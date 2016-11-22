#!/opt/swe/bin/perl -w


=pod

=head1 log foramt conversion

=head2 DESCRIPTION

This srcipts was used to del some useless infor in the file!




=head2 SCRIPT PARAMETER

=over 

=item input_filename

Path to the logfile which should be parsed

=item output_filename
At the same directory, named as "log_result.txt"

=example
sub_trace.pl log.txt

=back

=cut

################################################################################

# variables
my $line_last;
my $line_last_new;
use strict;
	
open(FILE1,"$ARGV[0]")||die "can't open $ARGV[0] file!\n";
open(FILE2,">$ARGV[0]_new");
print ("start first convert!\n");

while(<FILE1>)
{
	$line_last=$_;
	chomp($line_last);#去除换行
	$line_last =~ s/\s+//g;#去除空格
	#$line_last=s/[/n]//;
	#find the error information
	if($line_last=~/cc$/)
	{
		next;
	}
	if($line_last=~/c$/)
	{
		$line_last =~ s/SRC_PATH/CCROOT/;#
		$line_last_new = "$line_last"."c";
		print FILE2 "$line_last_new","\n";
		system "mv $line_last $line_last_new";
	}
	else
	{
		next;
	}	
}
close FILE1;
close FILE2;
system "rm -rf $ARGV[0].temp";
