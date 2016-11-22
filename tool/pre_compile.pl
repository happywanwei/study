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
my $libname;
my $filename1;
my $filename2;
use strict;
	
open(FILE1,"$ARGV[0]")||die "can't open $ARGV[0] file!\n";
open(FILE2,">$ARGV[0]_new");
print ("start convert!\n");

while(<FILE1>)
{
	$line_last=$_;
	chomp($line_last);#ȥ������
	#$line_last =~ s/\s+//g;#ȥ�����пո�
	##ȥ������ʼ�Ŀո�
	#ȥ���н�β�Ŀո�
	#$line_last=s/[/n]//;
	#find the error information
	#�ҳ���.c����β���ļ����������ļ���
	if($line_last=~/\.cc$/)
	{
		print FILE2 "$line_last","\n";
	}
	elsif($line_last=~/\.c$/)
	{
		$line_last_new = "$line_last"."c";#���c�ַ�����β
		print FILE2 "$line_last"."c","\n";
		$line_last =~ s/SRC_PATH/CCROOT/;#��CCROOT�滻SRC_PATH,�滻�ַ�
		$line_last_new =~ s/SRC_PATH/CCROOT/;
		system "mv $line_last $line_last_new";
	}
	#�ҳ���.o���ļ�����Ԥ����
	elsif($line_last=~/\.o$/|$line_last=~/\.o $/)
	{
		$line_last =~ s/SRC_PATH/CCROOT/;#�滻�ַ�
		$line_last_new=$line_last;
		$line_last_new =~ s/\.o/\.a/;#�滻�ַ�
		#print "line_last_new=",$line_last_new;
		#print "line_last=",$line_last;
		system "arm-none-linux-gnueabi-ar r $line_last_new $line_last";
		$libname =substr($line_last_new,rindex($line_last_new,"\/"));#��ȡ���һ��"/"����ִ�
		$libname =~ s/\//lib/;
		print FILE2 "$libname","\n";
	}
	elsif($line_last=~/\.a$/|$line_last=~/\.a $/)
	{
		$libname =substr($line_last,rindex($line_last,"\/"));#��ȡ���һ��"/"����ִ�
		$libname =~ s/\///;
		print FILE2 "$libname","\n";
	}
	else
	{
		print FILE2 "$line_last","\n";
	}	
}
close FILE1;
close FILE2;
#UCUNBGBSP_H
$filename1 ="\$CCROOT/enodeb_pq3/itest/l2_stub/stub/bsp.h"; 
$filename2 ="\$CCROOT/enodeb_pq3/itest/l2_stub/stub/bsp.h.temp";
die "oops, this file is exist\n" if -e "$filename2";#��ѯ�ļ���Ŀ¼�Ƿ����
system "mv $filename1 $filename2";
open(FILE1,"$filename2")||die "can't open $filename2\n";
open(FILE2,">$filename1")||die "can't open $filename1\n";
while(<FILE1>)
{
	$line_last=$_;
	if($line_last=~/UCUNBGBSP_H/)
	{
		$line_last =~ s/UCUNBGBSP_H/UCUNBGBSP_STUB_H/;
	}
	print FILE2 "$line_last";
}
close FILE1;
close FILE2;
system "rm -rf $filename2";