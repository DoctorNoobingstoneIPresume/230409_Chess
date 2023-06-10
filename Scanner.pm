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
	my $self              = @_ ? shift : Azzert ();
	my $sPathName0        = @_ ? shift : Azzert ();
	my $rasIncludeFolders = @_ ? shift : [];
	my $rhsPathNamesAbove = @_ ? shift : {};
	# [2023-06-10]
	if (1)
	{
		foreach my $s (@$rasIncludeFolders)
		{
			$s =~ s#[\\]#[/]#g;
			
			if ($s =~ m#(.*)/#)
			{
				#printf ("Modifying %s to %s...\n", "\"${s}\"", "\"${1}\"");
				$s = $1;
			}
		}
	}
	
	my $rhSourceFiles = $self->{rhSourceFiles};
	my $sourcefile = undef;
	{
		my $fh;
		do
		{
			if (exists ($rhSourceFiles->{$sPathName0}))
			{
				return $rhSourceFiles->{$sPathName0};
			}
			
			# [2023-06-10] TODO: Is there a chance that a file is opened and read multiple times (by reciprocal inclusion) ?
			
			if (! open ($fh, '<', $sPathName0))
			{
				printf ("Scanner::Scan: We have failed to open \"%s\".\n", $sPathName0);
				last;
			}
			
			my @asStat = stat ($fh);
			if (! @asStat)
			{
				printf ("Scanner::Scan: We have failed to stat \"%s\".\n", $sPathName0);
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
							#printf (": %s\n", $sLine);
							$hksNames1 {$1} = 1;
						}
					}
				}
				
				$sourcefile->IncludeNames (\%hksNames1);
				
				my @asPathNames1 = ();
				{
					foreach my $sName1 (sort keys %hksNames1)
					{
						foreach my $sIncludeFolder (@$rasIncludeFolders)
						{
							my $sPathName1 = $sIncludeFolder . ($sIncludeFolder =~ m#/$# ? '' : '/') . $sName1;
							my $sourcefile1 = $self->Scan ($sPathName1, $rasIncludeFolders);
							if ($sourcefile1)
							{
								push (@asPathNames1, $sPathName1);
								if ($sourcefile1->MaxModifyTime () > $sourcefile->MaxModifyTime ())
								{
									$sourcefile->MaxModifyTime     ($sourcefile1->MaxModifyTime     ());
									$sourcefile->MaxModifyPathName ($sourcefile1->MaxModifyPathName ());
								}
							}
						}
					}
				}
				
				$sourcefile->IncludePathNames (\@asPathNames1);
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
			$sRet .= IndentWithTitle ($sourcefile->ToString (), $ks);
		}
	}
	
	return $sRet;
}

1;
