#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int arr[50];
int count=0;

class product 
{
	int product_number;
    string name;
    float price, qty, tax, discount;
public:
	
	void create_product()
	{
		label:
		cout << "\nPlease Enter The Product No: ";
        cin >> product_number;
		for(int i=0;i<count;i++)
		{
			if(arr[i]==product_number)
			{
				cout<<"PRODUCT NUMBER ALREADY EXIST"<<endl;
				goto label;
			}
		}
		cout << "\n\nPlease Enter The Name of The Product ";
		cin.ignore(80,'\n');
		getline(cin, name); 
		cout << "\nPlease Enter The Price of The Product ";
        cin >> price;
        cout << "\nPlease Enter The Discount (%) ";
        cin >> discount;
	}

	void show_product()
	{
		cout << "\nThe Product No. of The Product : " << product_number;
		cout << "\nThe Name of The Product : ";
		cout<<name;
        cout << "\nThe Price of The Product : " << price;
        cout << "\nDiscount : " << discount;
	}
	int return_product_number() 
        {
            return product_number;
        }
	float return_price() 
        {
            return price;
        }
	string return_name() 
        {
            return name;
        }
	float return_discount() 
        {
            return discount;
        }
}; 
fstream fp;
product pr;

void checkproductno()
{
	count=0;
	fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(pr))) 
    {
		arr[count]=pr.return_product_number();
		cout<<arr[count]<<endl;
		count++;
    }
    fp.close();
}
void write_product() 
{
	checkproductno();
    fp.open("Shop.dat", ios::out | ios::app);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(pr));
    fp.close();
    cout << "\n\nThe Product Has Been Created ";
	cout<<endl;
    system("pause");
}
void display_all() 
{
    system("CLS");
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(pr))) 
    {
        pr.show_product();
        cout << "\n\n====================================\n";
        cout<<endl;
    }
    fp.close();
	cout<<endl;
    system("pause");
}
void display_sp(int n) 
{
    int flag = 0;
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(pr))) 
    {
        if (pr.return_product_number() == n) 
        {
            system("CLS");
            pr.show_product();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
        cout << "\n\nrecord not exist";
	cout<<endl;
    system("pause");
}
void modify_product() 
{
    int no, found = 0;
    system("CLS");
    cout << "\n\n\tTo Modify ";
    label:
		cout << "\nPlease Enter The Product No: ";
        cin >> no;
		for(int i=0;i<count;i++)
		{
			if(arr[i]==no)
			{
				cout<<"PRODUCT NUMBER ALREADY EXIST"<<endl;
				goto label;
			}
		}
    fp.open("Shop.dat", ios:: in | ios::out);
    while (fp.read((char * ) & pr, sizeof(pr)) && found == 0) 
    {
        if (pr.return_product_number() == no) 
        {
            pr.show_product();
            cout << "\nPlease Enter The New Details of Product" << endl;
            pr.create_product();
            int pos = -1 * sizeof(pr);
            fp.seekp(pos, ios::cur);
            fp.write((char * ) & pr, sizeof(product));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
	cout<<endl;
    system("pause");
}
void delete_product() 
{
    int no;
    system("CLS");
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & pr, sizeof(pr))) 
    {
        if (pr.return_product_number() != no) 
        {
            fp2.write((char * ) & pr, sizeof(pr));
        }
    }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat", "Shop.dat");
    cout << "\n\n\tRecord Deleted ..";
    cout<<endl;
	system("pause");
}

void menu() 
{
    system("CLS");
    fp.open("Shop.dat", ios:: in );
    if (!fp) 
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File ";
        cout << "\n\n\n Program is closing ....";
		cout<<endl;
        system("pause");
        exit(0);
    }

    cout << "\n\n\t\tProduct MENU\n\n";
    cout << "====================================================\n";
    cout << "P.NO.\t\tNAME\t\tPRICE\n";
    cout << "====================================================\n";

    while (fp.read((char * ) & pr, sizeof(pr))) 
    {
        cout << pr.return_product_number() << "\t\t" << pr.return_name() << "\t\t" << pr.return_price() << endl;
    }
    fp.close();
}


void place_order() 
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    do 
    {
        cout << "\n\nEnter The Product No. Of The Product : ";
        cin >> order_arr[c];
        cout << "\nQuantity in number : ";
        cin >> quan[c];
        c++;
        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You For Placing The Order";
	cout<<endl;
    system("pause");
    system("CLS");
    cout << "\n\n******************************** INVOICE ************************\n";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n ";
    for (int x = 0; x <= c; x++) 
    {
        fp.open("Shop.dat", ios:: in );
        fp.read((char * ) & pr, sizeof(pr));
        while (!fp.eof()) 
        {
            if (pr.return_product_number() == order_arr[x]) 
            {
                amt = pr.return_price() * quan[x];
                damt = amt - (amt * pr.return_discount() / 100);
                cout << "\n" << order_arr[x] << "\t" << pr.return_name() <<
                    "\t" << quan[x] << "\t\t" << pr.return_price() << "\t" << amt << "\t\t" << damt;
                total += damt;
            }
            fp.read((char * ) & pr, sizeof(pr));
        }

        fp.close();
    }
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
	cout<<endl;
}


void intro() 
{
    system("CLS");
	cout<<"\n\n\n\t\t\t\t\t\t";
    cout << "SUPER MARKET";
    cout<<"\n\n\n\t\t\t\t\t\t";
    cout << "BILLING";
    cout<<"\n\n\n\t\t\t\t\t\t";
    cout << "PROJECT";
    cout << "\n\nDEVELOPED BY : MIAN AMIR SALAR";
    cout << "\n\nSAP : 14772";
	cout<<endl;
    system("pause");

}

void admin_menu() 
{
    system("CLS");
    char ch2;
    cout << "\n\n\n\tADMIN MENU";
    cout << "\n\n\t1.CREATE PRODUCT";
    cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
    cout << "\n\n\t3.QUERY ";
    cout << "\n\n\t4.MODIFY PRODUCT";
    cout << "\n\n\t5.DELETE PRODUCT";
    cout << "\n\n\t6.VIEW PRODUCT MENU";
    cout << "\n\n\t7.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-7) ";
    ch2 = getche();
    switch (ch2) 
    {
    case '1':
        system("CLS");
        write_product();
		admin_menu();
        break;
    case '2':
        display_all();
		admin_menu();
        break;
    case '3':
        int num;
        system("CLS");
        cout << "\n\n\tPlease Enter The Product No. ";
        cin >> num;
        display_sp(num);
		admin_menu();
        break;
    case '4':
        modify_product();
		admin_menu();
        break;
    case '5':
        delete_product();
		admin_menu();
        break;
    case '6':
        menu();
		cout<<endl;
        system("pause");
		admin_menu();
    case '7':
        break;
    default:
        cout << "\a";
        admin_menu();
    }
}
void main() 
{
    char ch;
    intro();
    do 
    {
        system("CLS");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. CUSTOMER";
        cout << "\n\n\t02. ADMINISTRATOR";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3) ";
        ch = getche();
        switch (ch) 
        {
        case '1':
            system("CLS");
            place_order();
			cout<<endl;
			system("pause");
            break;
        case '2':
			{
			system("cls");
			int pass;
			cout<<"ENTER PASSWORD: ";
			cin>>pass;
			if(pass==123)
			{
            admin_menu();
			}
			else
			{
			cout<<"WRONG PASSWORD ENTERED"<<endl;
			cout<<endl;
			system("pause");
			}
            break;
			}
        case '3':
            exit(0);
        default:
            cout << "\a";
        }
    } while (ch != '3');
}