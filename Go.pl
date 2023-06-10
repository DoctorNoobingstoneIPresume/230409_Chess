#!/usr/bin/env perl
use strict; use warnings;
use Scanner;
use Util;

sub my_system
{
	{ use IO::Handle; STDOUT->flush (); }
	
	my $iResult = system (@_);
	if ($iResult)
	{
		print (IndentWithTitle (ArrayToString (\@_), "Failure (code ${iResult}):"));
		{ use IO::Handle; STDOUT->flush (); }
		exit (1);
	}
	
	return $iResult;
}

sub SplitToJustNameAndJustExt
{
	my $s0 = @_ ? shift : Azzert ();
	
	my $sJustName = $s0;
	my $sJustExt  = '';
	{
		if ($s0 =~ m#(.*)[.](.*)#)
		{
			$sJustName = $1;
			$sJustExt  = $2;
		}
	}
	
	return ($sJustName, $sJustExt);
}

sub Main
{
	#printf ("Hello, World of Perl !\n");
	
	my $sBuildFolder = "_Build";
	my_system ('mkdir', '-p', $sBuildFolder);
	
	my @asUnits;
	{
		foreach my $sLine (`ls`)
		{
			chomp ($sLine);
			if ($sLine =~ m#\.cpp$#)
			{
				#printf (": %s\n", $sLine);
				push (@asUnits, $sLine);
			}
		}
	}
	
	# [2023-06-10] TODO: Eliminate the following exit:
	#{ use IO::Handle; STDOUT->flush (); } exit (0);
	
	# [2023-04-11] TODO: Support for unittests...
	
	# Compilation:
	my @asObjectsCommon;
	my @asObjectsUT;
	my @asObjectsMain;
	my @asObjects;
	{
		foreach my $sUnit (@asUnits)
		{
			my ($sUnitJustName, $sUnitJustExt) = SplitToJustNameAndJustExt ($sUnit);
			
			my $sObject = "${sBuildFolder}/${sUnitJustName}.o";
			
			push (@asObjects, $sObject);
			
			if    ($sUnitJustName =~ m#_UT$#)
			{
				push (@asObjectsUT    , $sObject);
			}
			elsif ($sUnitJustName eq 'Main')
			{
				push (@asObjectsMain  , $sObject);
			}
			else
			{
				push (@asObjectsCommon, $sObject);
			}
		}
	}
	my $scanner = Scanner->CreateObject ();
	{
		foreach my $sUnit (@asUnits)
		{
			printf ("Scanning \"%s\":\n{\n", $sUnit);
			my $sourcefile = $scanner->Scan ($sUnit, {'./' => 1});
			if (defined ($sourcefile))
			{
				printf ("%s\n", $sourcefile->ToString ());
			}
			else
			{
				printf ("undef\n");
			}
			printf ("}\n\n");
			
			#last;
		}
	}
	{
		foreach my $sUnit (@asUnits)
		{
			my ($sUnitJustName, $sUnitJustExt) = SplitToJustNameAndJustExt ($sUnit);
			
			my $sObject = "${sBuildFolder}/${sUnitJustName}.o";
			my @asArgs =
			(
				'g++',
				'-std=c++11',
				'-I', $ENV {'BOOST_ROOT'},
				'-g',
				'-c', $sUnit,
				'-o', $sObject
			);
			
			my $sourcefile = $scanner->Get ($sUnit);
			Azzert ($sourcefile);
			
			my $tObject = 0;
			my $fhObject;
			do
			{
				if (! open ($fhObject, '<', $sObject))
				{
					printf ("We have failed to open object \"%s\".\n", $sObject);
					last;
				}
				
				my @asStat = stat ($fhObject);
				if (! @asStat)
				{
					printf ("We have failed to stat \"%s\".\n", $sObject);
					last;
				}
				
				$tObject = $asStat [9];
			} while (0);
			if ($fhObject) { close ($fhObject); }
			
			my $bProcess = $sourcefile->MaxModifyTime () >= $tObject;
			
			if (! $bProcess)
			{
				next;
			}
			
			printf ("Compiling => %s...\n{\n", "\"${sObject}\"");
			#printf ("%s\n", ArrayToString (\@asArgs));
			
			my_system (@asArgs);
			
			printf ("}\n\n");
		}
	}
	
	# Archiving:
	my $sArchive = "${sBuildFolder}/zzz.a";
	{
		my_system ('rm', '-f', $sArchive);
		
		my @asArgs =
		(
			'ar',
			'-rsT',
			$sArchive,
			@asObjectsCommon
		);
		
		{
			printf ("Archiving => %s...\n{\n", "\"${sArchive}\"");
			my_system (@asArgs);
			my_system ('ranlib', $sArchive);
			printf ("}\n\n");
		}
	}
	
	# Linking:
	{
		my @asObjectsLink =
		(
			@asObjectsMain,
			@asObjectsUT
		);
		
		foreach my $sObjectLink (@asObjectsLink)
		{
			my $sObjectLinkJustName = (&SplitToJustNameAndJustExt ($sObjectLink)) [0];
			
			printf ("Linking => %s...\n{\n", "\"${sObjectLinkJustName}\"");
			
			my_system
			(
				'g++',
				'-g',
				$sObjectLink,
				$sArchive,
				'-o', $sObjectLinkJustName
			);
			
			printf ("}\n\n");
		}
	}
	
	# Testing:
	{
		foreach my $sObjectLink (@asObjectsUT)
		{
			my $sObjectLinkJustName = (&SplitToJustNameAndJustExt ($sObjectLink)) [0];
			printf ("Testing %s...\n{\n", "\"${sObjectLinkJustName}\"");
			my_system ($sObjectLinkJustName);
			printf ("}\n\n");
		}
	}
	
	return 0;
}

my $iResult = &Main ();
if ($iResult)
{
	printf "Main has failed !\n";
	{ use IO::Handle; STDOUT->flush (); }
	exit ($iResult);
}
