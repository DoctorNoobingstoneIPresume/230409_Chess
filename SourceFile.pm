use strict; use warnings;
package SourceFile;
use Util;

sub CreateObject
{
	my $sClassName = @_ ? shift : Azzert ();
	
	my $self = bless ({}, $sClassName);
	{
		$self->{rhksIncludeNames}     = {};
		$self->{rhksIncludePathNames} = {};
		$self->{tModify}              = 0;
		$self->{sMaxModifyPathName}   = '';
		$self->{tMaxModify}           = 0;
	}
	
	return $self;
}

sub IncludeNames
{
	my $self = @_ ? shift : Azzert ();
	if (@_)
	{
		my $value = shift;
		$self->{rhksIncludeNames} = $value;
		return $self;
	}
	else
	{
		return $self->{rhksIncludeNames};
	}
}

sub IncludePathNames
{
	my $self = @_ ? shift : Azzert ();
	if (@_)
	{
		my $value = shift;
		$self->{rhksIncludePathNames} = $value;
		return $self;
	}
	else
	{
		return $self->{rhksIncludePathNames};
	}
}

sub ModifyTime
{
	my $self = @_ ? shift : Azzert ();
	if (@_)
	{
		my $value = shift;
		$self->{tModify} = $value;
		return $self;
	}
	else
	{
		return $self->{tModify};
	}
}

sub MaxModifyPathName
{
	my $self = @_ ? shift : Azzert ();
	if (@_)
	{
		my $value = shift;
		$self->{sMaxModifyPathName} = $value;
		return $self;
	}
	else
	{
		return $self->{sMaxModifyPathName};
	}
}

sub MaxModifyTime
{
	my $self = @_ ? shift : Azzert ();
	if (@_)
	{
		my $value = shift;
		$self->{tMaxModify} = $value;
		return $self;
	}
	else
	{
		return $self->{tMaxModify};
	}
}

sub PrettyTime
{
	# [2023-06-10] https://stackoverflow.com/questions/15064446/convert-unix-timestamp-to-a-readable-date-in-perl
	use Time::Piece;
	
	my $t = @_ ? shift : Azzert ();
	
	return sprintf
	(
		"%10u%s",
		$t,
		$t ? ' = ' . localtime ($t)->strftime ('%F %T %z') : ''
	);
}

sub ToString
{
	my $self = @_ ? shift : Azzert ();
	
	my $sRet = '';
	{
		my $sFormat = '%F %T %z';
		
		{
			my $s0 = '';
			{
				foreach my $ks (sort keys % {$self->{rhksIncludeNames}})
				{
					if (length ($s0)) { $s0 .= ', '; }
					if (1)            { $s0 .= "\"${ks}\" => ..."; }
				}
			}
			
			$sRet .= 'rhksIncludeNames    ' . "{${s0}}.\n";
		}
		
		{
			my $s0 = '';
			{
				foreach my $ks (sort keys % {$self->{rhksIncludePathNames}})
				{
					if (length ($s0)) { $s0 .= ' '; }
					if (1)            { $s0 .= "\"${ks}\" => ..."; }
				}
			}
			
			$sRet .= 'rasIncludePathNames ' . "[${s0}].\n";
		}
		
		my $t;
		$sRet .= 'tModify             ' . PrettyTime ($self->{tModify   }) . ".\n";
		
		$sRet .= 'tMaxModify          ' . PrettyTime ($self->{tMaxModify}) . ".\n";
		
		$sRet .= 'sMaxModifyPathName  ' . "\"" . $self->{sMaxModifyPathName} . "\"\n";
	}
	
	# [2023-06-10]
	#return IndentWithTitle ($sRet, 'SourceFile');
	return $sRet;
}

1;
