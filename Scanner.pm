use strict; use warnings;
package Scanner;
use SourceFile;
use Util;

sub CreateObject
{
	my $sClassName = @_ ? shift : Azzert ();
	
	my $self = bless ({}, $sClassName);
	{
		$self->{rhSourceFiles} = {};
	}
	
	return $self;
}

sub Get
{
	my $self              = @_ ? shift : Azzert ();
	my $sPathName0        = @_ ? shift : Azzert ();
	
	my $rhSourceFiles = $self->{rhSourceFiles};
	return exists ($rhSourceFiles->{$sPathName0}) ? $rhSourceFiles->{$sPathName0} : undef;
}

sub Scan
{
	my $sPathName0         = scalar (@_) >= 2 ? $_ [1] : Azzert ();
	my $iLevel             = scalar (@_) >= 5 ? $_ [4] : 0;
	my $sIndent            = IndentPrefix ($iLevel);
	
	printf ("%sScanning \"%s\":\n%s{\n", $sIndent, $sPathName0, $sIndent);
	my $sourcefileRet = &Do_Scan (@_);
	printf ("%s}\n\n", $sIndent);
	
	return $sourcefileRet;
}

sub Do_Scan
{
	my $self               = @_ ? shift : Azzert ();
	my $sPathName0         = @_ ? shift : Azzert ();
	my $rhksIncludeFolders = @_ ? shift : {};
	my $rhksPathNamesAbove = @_ ? shift : {};
	my $iLevel             = @_ ? shift : 0;
	my $sIndent            = IndentPrefix ($iLevel + 1);
	# [2023-06-10]
	if (1)
	{
		my %hksIncludeFolders_New = ();
		foreach my $ks (sort keys %$rhksIncludeFolders)
		{
			$ks =~ s#[\\]#[/]#g;
			
			if ($ks =~ m#(.*)/#)
			{
				#printf ("%s" . "Modifying %s to %s...\n", $sIndent, "\"${s}\"", "\"${1}\"");
				$ks = $1;
			}
			
			$hksIncludeFolders_New {$ks} = 1;
		}
		
		$rhksIncludeFolders = \%hksIncludeFolders_New;
	}
	
	my $rhSourceFiles = $self->{rhSourceFiles};
	my $sourcefile = undef;
	{
		my $fh;
		do
		{
			if (exists ($rhSourceFiles->{$sPathName0}))
			{
				$sourcefile = $rhSourceFiles->{$sPathName0};
				printf ("%s" . "Scanner::Scan: Returning from cache (%s).\n", $sIndent, $sourcefile ? 'defined' : 'undef');
				return $sourcefile;
			}
			
			# [2023-06-10] TODO: Is there a chance that a file is opened and read multiple times (by reciprocal inclusion) ?
			
			if (! open ($fh, '<', $sPathName0))
			{
				printf ("%s" . "Scanner::Scan: We have failed to open \"%s\".\n", $sIndent, $sPathName0);
				last;
			}
			
			my @asStat = stat ($fh);
			if (! @asStat)
			{
				printf ("%s" . "Scanner::Scan: We have failed to stat \"%s\".\n", $sIndent, $sPathName0);
				last;
			}
			
			$sourcefile = SourceFile->CreateObject ();
			{
				my $t0 = $asStat [9];
				$sourcefile->ModifyTime        ($t0);
				$sourcefile->MaxModifyTime     ($t0);
				$sourcefile->MaxModifyPathName ($sPathName0);
				
				my %hksNames1 = ();
				{
					while (defined (my $sLine = <$fh>))
					{
						chomp ($sLine);
						if ($sLine =~ m@^\s*[#]\s*include\s+["<](.*)[">]\s*$@)
						{
							#printf ("%s" . ": %s\n", $sIndent, $sLine);
							$hksNames1 {$1} = 1;
						}
					}
				}
				
				$sourcefile->IncludeNames (\%hksNames1);
				
				$rhksPathNamesAbove->{$sPathName0} = 1;
				my %hksPathNames1 = ();
				{
					foreach my $sName1 (sort keys %hksNames1)
					{
						foreach my $ksIncludeFolder (sort keys %$rhksIncludeFolders)
						{
							my $sPathName1 = $ksIncludeFolder . ($ksIncludeFolder =~ m#/$# ? '' : '/') . $sName1;
							
							if (exists ($hksPathNames1 {$sPathName1}))
							{
								next;
							}
							
							if (exists ($$rhksPathNamesAbove {$sPathName1}))
							{
								printf ("%s" . "Scanner::Scan: Re-inclusion from %s: %s.\n", $sIndent, "\"${sPathName0}\"", "\"${sPathName1}\"");
								$hksPathNames1 {$sPathName1} = 1;
								next;
							}
							
							my $sourcefile1 = $self->Scan ($sPathName1, $rhksIncludeFolders, $rhksPathNamesAbove, $iLevel + 1);
							if ($sourcefile1)
							{
								$hksPathNames1 {$sPathName1} = 1;
								if ($sourcefile1->MaxModifyTime () > $sourcefile->MaxModifyTime ())
								{
									$sourcefile->MaxModifyTime     ($sourcefile1->MaxModifyTime     ());
									$sourcefile->MaxModifyPathName ($sourcefile1->MaxModifyPathName ());
								}
							}
						}
					}
				}
				
				$sourcefile->IncludePathNames (\%hksPathNames1);
			}
		} while (0);
		
		if ($fh)
		{
			close ($fh);
		}
	}
	
	$rhSourceFiles->{$sPathName0} = $sourcefile;
	
	return $sourcefile;
}

sub ToString
{
	my $self = @_ ? shift : Azzert ();
	
	my $sRet = '';
	{
		my $rhSourceFiles = $self->{rhSourceFiles};
		foreach my $ks (sort keys %$rhSourceFiles)
		{
			my $sourcefile = $rhSourceFiles->{$ks};
			$sRet .= IndentWithTitle ($sourcefile ? $sourcefile->ToString () : 'undef', $ks);
		}
	}
	
	return $sRet;
}

1;
