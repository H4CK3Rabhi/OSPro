import java.util.Scanner;
class bankaccount
{
int balance=0;
final Scanner sc= new Scanner(System.in);
void deposit(int amt)
{
balance+=amt;
}
int withdraw()
{
System.out.println("Please Enter Amount to wothdraw:");

int amt=sc.nextInt();
if(amt>balance)
{
return -1;
}
balance-=amt;
return balance;
}
}
class Testbankaccount
{
public static void main(String[] args)
{
bankaccount a=new bankaccount();
Scanner sc=new Scanner(System.in);
int amt=sc.nextInt();
a.deposit(amt);
int ne=a.withdraw();
if(ne==-1)
{
System.out.println("Insufficient Funds");
}
else
{
System.out.println(ne); 
}
}
}

