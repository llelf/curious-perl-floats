use Modern::Perl;

# This returns /exact/ result (modulo denormalized floats (module bugs)).
sub aparse {
    my ($x) = @_;

    $x =~ /(?<neg> -)? 0x
           (?<signif0> [0-9a-f]) (?: \. (?<signif> [0-9a-f]+))?
           p (?<exps> [+-])? (?<exp> [0-9]+)/x
	   or return;
    

    my $r = 0;
    for my $digit (reverse split //, $+{signif} // '') {
	$r += hex $digit;
	$r /= 16;
    }

    $r += hex $+{signif0};

    for (1 .. $+{exp}) {
	($+{exps} // '+') eq '+'
	    ? ($r *= 2)
	    : ($r /= 2);
    }

    $r = -$r if $+{neg};

    return $r;
}


my $mx = 0;
while (<> =~ /(\S+) (\S+)/) {
    my $exact = aparse($1);
    my $perl = eval($2);
    my $err = $exact - $perl;
    $err /= $exact if $exact != 0;

    #$err = 0 if ($exact == 0 || $perl == 0);

    if (abs($err) > $mx) {
	$mx = abs ($err);
	say "$exact $perl $err";
    }
}



