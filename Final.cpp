#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>
#include <conio.h>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

class Unbranded_Items
{
protected:
	//variables
	string category;
	string name;
	char count_grams;  // n = count , g = grams
	float quantity;
	float retail_price;
	float discounts;//one whole set (precentage)
	float promotions;//on one unit (number)

public:
	//Constructor
	Unbranded_Items(string Category = "f", string Name = "f", char Count_grams = '\0', float Quantity = 0, float Retail_price = 0, float Discounts = 0, float Promotions = 0) : category(Category), name(Name), count_grams(Count_grams), quantity(Quantity), retail_price(Retail_price), discounts(Discounts), promotions(Promotions) {}////////////////////////////

	//methods
	//stocking up if similer
	void stockup(float Quantity = 0)
	{
		quantity += Quantity;
	}
	//stocking down if similer
	void stockdown(float Quantity = 0)
	{
		quantity -= Quantity;
	}
	//return category
	string getcategory()
	{
		return category;
	}
	//return item name
	string get_name()
	{
		return name;
	}
	//return item name
	char get_measure()
	{
		return count_grams;
	}
	//add product types
	void set_products(bool initiate = 0, string Category = "", char Measure = '\0')
	{
		if (initiate == 0)
		{
			category = Category;
			gotoxy(80, 20); cout << "Enter the product retail price\t: "; cin >> retail_price;
			count_grams = Measure;
			gotoxy(80, 22); cout << "Enter the product name\t: "; cin.ignore(); getline(cin, name);
			gotoxy(80, 24); cout << "Enter the product quantity\t: "; cin >> quantity;
			gotoxy(80, 26); cout << "Discounts\t: "; cin >> discounts;
			gotoxy(80, 28); cout << "Promotions\t: "; cin >> promotions;
		}
	}
	//show item data
	void show(int x = 0, int y = 0, int Category_ID = 0, int Name_ID = 0, int edit = 0)//category-id- category index , name_id - name index
	{
		gotoxy(x, y + 0);	cout << "*********************************************************";
		gotoxy(x, y + 2);	cout << "Category ID \t\t:" << Category_ID;
		gotoxy(x, y + 3);	cout << "Product ID \t\t:" << Name_ID;
		gotoxy(x, y + 6);	cout << "Category \t\t:" << category;
		gotoxy(x, y + 7);	cout << "Product name \t\t:" << name;
		gotoxy(x, y + 8);	cout << "Measured using \t\t:" << count_grams;
		gotoxy(x, y + 9);	cout << "Available quantitiy \t:" << quantity;
		gotoxy(x, y + 10);	cout << "Retail price \t\t:" << retail_price;
		gotoxy(x, y + 11);	cout << "Available discounts \t:" << discounts;
		gotoxy(x, y + 12);	cout << "Available promotions \t:" << promotions;
		gotoxy(x, y + 15);	cout << "*********************************************************";
	}
};

class Branded_Items :public Unbranded_Items
{
private:
	string brand;
	string local_imported;
public:
	//Constructor
	Branded_Items(string Category = "f", string Name = "f", char Count_grams = '\0', float Quantity = 0, float Retail_price = 0, float Discounts = 0, float Promotions = 0, string Brand = "f", string Local_imported = "f") : Unbranded_Items(Category, Name, Count_grams, Quantity, Retail_price, Discounts, Promotions), brand(Brand), local_imported(Local_imported) {}//////////////////////

	//add product types
	void set_products(bool initiate = 0, string Category = "", char Measure = '\0')
	{
		Unbranded_Items::set_products(initiate, Category, Measure);
		if (initiate == 0)
		{
			gotoxy(80, 30); cout << "Brand of the product\t: "; cin.ignore(); getline(cin, brand);
			gotoxy(80, 32); cout << "Local/Imported (type and enter)\t: "; cin.ignore(); getline(cin, local_imported);
		}
	}

	//Methods
	void show(int x = 0, int y = 0, int Category_ID = 0, int Name_ID = 0, int edit = 0)//category-id- category index , name_id - name index
	{
		Unbranded_Items::show(x, y, Category_ID, Name_ID);
		gotoxy(x, y + 13);	cout << "Local/Imported\t\t:" << local_imported;
		gotoxy(x, y + 15);	cout << "*********************************************************";
	}
};

class Stocks
{
private:
	vector<vector<Unbranded_Items>> Unbranded;
	vector<vector<Branded_Items>> Branded;
public:
	void initiate_vectors()
	{
		vector <string> Category = { "Produce" , "Meat_&_Seafood" , "Grains" , "Bakery_products" , "Frozen_foods" , "Dairy_products"  , "Snacks_and_Sweets" , "Beverages" , "Health_&_Beauty" , "Condiments_&_Spices" };
		vector <char> Count_grams = { 'g' , 'g' , 'g' , 'n' , 'n' , 'n' , 'n' , 'n' , 'n' , 'n' };
		vector <int> Set ={0,0,0,0,0,0,0,0,0,0};

			ifstream file;
			file.open("Stocks.txt");
			
			int count; file>>count;
			for(int j=0;j<count;j++)
			{
					string cAtegory=""; file>>cAtegory;///////////////////////////////////////////////////////////
					string nAme=""; file>>nAme;///////////////////////////////////////////////////////////
					float qUantity=0; file>>qUantity;////////////////////////////////////////////////
					float rEtail_price=0;  file>>rEtail_price;//////////////////////////////////////////
					float dIscounts=0; file>>dIscounts;//////////////////////////////////////////////
					float pRomotions=0; file>>pRomotions;////////////////////////////////////////////////		
					string lOcal_imported="0";
					string bRand="0";
					if(cAtegory!="Produce"&&cAtegory!="Meat_&_Seafood")
					{
						file>>lOcal_imported;	
						file>>bRand;	
					}
				if(cAtegory=="Produce"||cAtegory=="Meat_&_Seafood")
				{
					for(int i=0;i<10;i++)
					{
						if(cAtegory==Category[i]&&Set[i]==0)
						{
							vector <Unbranded_Items> temp;
							Unbranded_Items obj(cAtegory, nAme , Count_grams[i] , qUantity , rEtail_price , dIscounts , pRomotions);////////
							temp.push_back(obj);
							Unbranded.push_back(temp);
							Set[i]=1;
							break;
						}
						if(cAtegory==Category[i]&&Set[i]==1)
						{
							Unbranded_Items obj(cAtegory, nAme , Count_grams[i] , qUantity , rEtail_price , dIscounts , pRomotions);////////
							Unbranded[i].push_back(obj);
							break;
						}
					}
				}
				if(cAtegory!="Produce"&&cAtegory!="Meat_&_Seafood")
				{
					for(int i=0;i<10;i++)
					{
						if(cAtegory==Category[i]&&Set[i]==0)
						{
							vector <Branded_Items> temp;
							Branded_Items obj(cAtegory, nAme , Count_grams[i] , qUantity , rEtail_price , dIscounts , pRomotions, bRand ,lOcal_imported);////////
							temp.push_back(obj);
							Branded.push_back(temp);
							Set[i]=1;
							break;
						}
						if(cAtegory==Category[i]&&Set[i]==1)
						{
							Branded_Items obj(cAtegory, nAme , Count_grams[i] , qUantity , rEtail_price , dIscounts , pRomotions , bRand ,lOcal_imported );////////
							
							Branded[i-2].push_back(obj);

							break;
						}
					}
				}	
			}
	}

	void showstock(int edit = 0)
	{
		gotoxy(90, 3 + 15 * edit);	cout << "***********************";
		gotoxy(90, 4 + 15 * edit);	cout << "Current stock available";
		gotoxy(90, 6 + 15 * edit);	cout << "***********************";
		int total=0;
		for(int i=0;i<Unbranded.size();i++)
		{
			for(int j=0;j<Unbranded[i].size();j++)
			{
				++total;
			}		
		}
		for(int i=0;i<Branded.size();i++)
		{
			for(int j=0;j<Branded[i].size();j++)
			{
				++total;
			}		
		}
		
		int columnlength01 = 0, columnlength02 = 0;
		if (total % 3 == 2)
		{
			columnlength01 = 1; columnlength02 = 1;
		}
		if (total % 3 == 1)
		{
			columnlength01 = 1;
		}
		columnlength01 += total / 3;
		columnlength02 += total / 3;
		int left = 0, middle = 0, right = 0;
		for (int i = 0; i < Unbranded.size(); i++)
		{
			for (int j = 0; j < Unbranded[i].size(); j++)
			{
				if (columnlength01-- > 0)
				{
					Unbranded[i][j].show(8, 10 + (left++) * 17 + 15 * edit, i, j, edit);
				}
				else if (columnlength02-- > 0)
				{
					Unbranded[i][j].show(72, 10 + (middle++) * 17 + 15 * edit, i, j, edit);
				}
				else
				{
					Unbranded[i][j].show(136, 10 + (right++) * 17 + 15 * edit, i, j, edit);
				}
			}
		}
		for (int i = 0; i < Branded.size(); i++)
		{
			for (int j = 0; j < Branded[i].size(); j++)
			{
				if (columnlength01-- > 0)
				{
					Branded[i][j].show(8, 10 + (left++) * 17 + 15 * edit, Unbranded.size() + i, j, edit);
				}
				else if (columnlength02-- > 0)
				{
					Branded[i][j].show(72, 10 + (middle++) * 17 + 15 * edit, Unbranded.size() + i, j, edit);
				}
				else
				{
					Branded[i][j].show(136, 10 + (right++) * 17 + 15 * edit, Unbranded.size() + i, j, edit);
				}
			}
		}
	}

	void stock_up_down(string Category, string Name, float Quantity, char up_down) //Up 'u' down 'd'
	{
		for (int i = 0; i < Branded.size(); i++)
		{
			if (Branded[i][0].getcategory() == Category)
			{
				for (int j = 0; j < Branded[i].size(); j++)
				{
					if (Branded[i][j].get_name() == Name)
					{
						if (up_down == 'u' || up_down == 'U')
						{
							Branded[i][j].stockup(Quantity);
						}
						if (up_down == 'd' || up_down == 'D')
						{
							Branded[i][j].stockdown(Quantity);
						}
					}
				}
			}
		}
		for (int i = 0; i < Unbranded.size(); i++)
		{
			if (Unbranded[i][0].getcategory() == Category)
			{
				for (int j = 0; j < Unbranded[i].size(); j++)
				{
					if (Unbranded[i][j].get_name() == Name)
					{
						if (up_down == 'u' || up_down == 'U')
						{
							Unbranded[i][j].stockup(Quantity);
						}
						if (up_down == 'd' || up_down == 'D')
						{
							Unbranded[i][j].stockdown(Quantity);
						}
					}
				}
			}
		}
	}

	void add_category(string Categoryname = "", char Measured_using = '\0', bool Branded_or_not = 1)//1 if Branded , 0 if not  
	{
		if (Branded_or_not == 1)
		{
			vector <Branded_Items> temp;
			Branded_Items obj(Categoryname, "fr", Measured_using);////////
			temp.push_back(obj);
			Branded.push_back(temp);
		}
		else
		{
			vector <Unbranded_Items> temp;
			Unbranded_Items obj(Categoryname, "fr", Measured_using);////////
			temp.push_back(obj);
			Unbranded.push_back(temp);
		}
	}

	void add_product() 
	{
		for (int i = 0; i < Unbranded.size(); i++)
		{
			gotoxy(20, 12 + 2 * i); cout << i << "\t: " << Unbranded[i][0].getcategory();
		}
		for (int j = 0; j < Branded.size(); j++)
		{
			gotoxy(20, 12 + 2 * (Unbranded.size() + j)); cout << Unbranded.size() + j << "\t: " << Branded[j][0].getcategory();
		}
		gotoxy(20, 6); cout << "Enter the ID number of the category : ";
		int num;
		gotoxy(62, 6); cin >> num; //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (num < Unbranded.size())
		{
			Unbranded_Items obj;
			obj.set_products(0, Unbranded[num][0].getcategory(), Unbranded[num][0].get_measure());
			obj.show();
			Unbranded[num].push_back(obj);
			system("cls");
		}
		else
		{
			num -= Unbranded.size();
			Branded_Items obj;
			obj.set_products(0, Branded[num][0].getcategory(), Branded[num][0].get_measure());
			Branded[num].push_back(obj);
			system("cls");
		}	
	}
	
	void stock_down(string &Category , string &Name , float &Quantity )
	{
		showstock(1);
		
		gotoxy(20, 6); cout << "Enter the Category (Exactly as it is in the stocks)   :";
		string category;
		gotoxy(100, 6); cin>>category;	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		Category=category;
		gotoxy(20, 8); cout << "Enter the Name (Exactly as it is in the stocks)       :";
		string name;
		gotoxy(100, 8); cin>>name;	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		Name=name;
		gotoxy(20, 10); cout << "Enter the quantity you want to reduce from the stock  :";
		float quantity;
		gotoxy(100, 10); cin>>quantity;	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		Quantity=quantity;
		
		system("cls");
	}	
	
};

//Supplies

class Supply
{
	protected: 
		string name_of_the_item;
		string brand_of_the_item;
		string category;
		int quantity;
		int availableQuantity;
		char measurement;
		string origin;//
		string date_of_arrival_at_the_supermarket;//
		bool status;//pending or not
		
	public:
		Supply(string Name_of_the_item = "", string Brand_of_the_item = "", string Category = "", int Quantity = 0, int AvailableQuantity = 0, char Measurement = 'g', string Origin = "", string Date_of_arrival_at_the_supermarket = "", bool Status = 1) : name_of_the_item(Name_of_the_item), brand_of_the_item(Brand_of_the_item), category(Category), quantity(Quantity), availableQuantity(AvailableQuantity), measurement(Measurement), origin(Origin), date_of_arrival_at_the_supermarket(Date_of_arrival_at_the_supermarket), status(Status) {}
		
		void setData(bool initiate = 0, string Category = "", char Measure = '\0')
		{
			gotoxy(80, 20);	cout<<"Enter the name of the item : ";
			cin.ignore();
			getline(cin, name_of_the_item);
	
			gotoxy(80, 22);	cout<<"Enter the category which the item belongs : ";
			getline(cin, category);
	
			gotoxy(80, 24);cout<<"Enter the brand of the item (enter '/' if there is no brand) : ";
			getline(cin, brand_of_the_item);
	
			gotoxy(80, 26);cout<<"Enter the quantity : ";
			cin>>quantity;
	
			availableQuantity = quantity;
		
			gotoxy(80, 28);cout<<"Enter the method used to measure the quantity (g- grams, c- count) : ";
			cin>>measurement;
	
			cin.ignore();
	
			gotoxy(80, 30);cout<<"Enter the date of arrival at the supermarket (DD/MM/YYYY) : ";
			getline(cin, date_of_arrival_at_the_supermarket);
			
		}
		
		void showData(int x = 0, int y = 0)
		{

			gotoxy(x, y + 0);	cout << "*********************************************************";
			gotoxy(x, y + 2);cout<<"Name of the item \t\t\t: "<<name_of_the_item<<endl;
			gotoxy(x, y + 4);cout<<"Category \t\t\t\t: "<<category<<endl;
	
			gotoxy(x, y + 6);cout<<"Brand of the item \t\t\t: "<<brand_of_the_item<<endl;

			gotoxy(x, y + 8);cout<<"Quantity \t\t\t\t: "<<quantity<<(measurement=='g'? " grams":" ")<<endl;
	
			gotoxy(x, y + 10);cout<<"Origin \t\t\t\t\t: "<<origin<<endl;
			gotoxy(x, y + 12);cout<<"Date of arrival at the supermarket \t: "<<date_of_arrival_at_the_supermarket<<endl;
	
			if(status)
			{		
				gotoxy(x, y + 14);cout<<"Stock status \t\t\t\t: Pending"<<endl;
				gotoxy(x, y + 16);cout<<"Available quantity to be added\t\t: "<<availableQuantity<<(measurement=='g'? " grams":" ");
			}
			else
			{
				gotoxy(x, y + 14);cout<<"Status       \t\t\t\t: Completely added to the stock"<<endl;		
			}
		
			gotoxy(x, y + 18);	cout << "*********************************************************";	
			
			
				
		}

		void remove_pending_goods(string Category , string Name , float &Quantity)
		{
			if(Category==category && Name==name_of_the_item)
			{				
				availableQuantity -= Quantity;
				     	
				if(availableQuantity<=0)
				{     
						availableQuantity=0;       			//1-pending, 0-added to the stock
						status = 0; 				
			 	}
			}
		}
								
		string get_name_of_the_item()
		{
			return name_of_the_item;
		}	
				
		string get_brand_of_the_item()
		{
			return brand_of_the_item;
		}
		
		string get_category()
		{
			return category;
		}
			
		int get_quantity()
		{
			return quantity;
		}
			
		bool get_status()
		{
			return status;
		}
			
		int get_availableQuantity()
		{
			return availableQuantity;
		}
	
};

class Local_Supply : public Supply
{
	private:
		string date_of_depature;
		string vehicle;
		
	public:
		Local_Supply(string Date_of_depature = "", string Vehicle = "") : date_of_depature(Date_of_depature), vehicle(Vehicle) {}
		
		
		void setData(bool initiate = 0, string Category = "", char Measure = '\0')
		{
			Supply::setData();
			cout<<endl;
			gotoxy(80, 32);cout<<"Enter the origin (farm / factory) : ";
			getline(cin, origin);
			
			gotoxy(80, 34);cout<<"Enter the date of depature from the "<<origin<<" (DD/MM/YYYY) : ";
			getline(cin, date_of_depature);
			
			gotoxy(80, 36);cout<<"Enter the registration number of the vehicle : ";
			getline(cin, vehicle);
			
		}
		
		void showData(int x = 0, int y = 0)
		{
			Supply::showData(x, y);
			
			gotoxy(x, y + 18); cout<<"                                                                                   ";
			gotoxy(x, y + 18); cout<<"Date of depature from the "<<origin<<" \t\t: "<<date_of_depature<<endl;
			gotoxy(x, y + 20); cout<<"Vehicle \t\t\t\t: "<<vehicle<<endl;
			gotoxy(x, y + 22);	cout << "*********************************************************";
		}
		
};

class International_Supply : public Supply
{
	private:
		string date_of_arrival_at_the_local_harbour;
		string shipNumber;
		
	public:
		International_Supply(string Date_of_arrival_at_the_local_harbour = "", string ShipNumber = "") : date_of_arrival_at_the_local_harbour(Date_of_arrival_at_the_local_harbour), shipNumber(ShipNumber) {}


		void setData(bool initiate = 0, string Category = "", char Measure = '\0')
		{
			Supply::setData();
			
			gotoxy(80, 32);cout<<"Enter the origin (name of the country) : ";
			getline(cin, origin);
			
			gotoxy(80, 34);cout<<"Enter the date of arrival at the local harbour (DD/MM/YYYY) : ";
			getline(cin, date_of_arrival_at_the_local_harbour);
			
			gotoxy(80, 36);cout<<"Enter the ship number : ";
			getline(cin, shipNumber);
			
			
			
				
		}
		
		void showData(int x = 0, int y = 0)
		{
			Supply::showData(x , y);
			
			gotoxy(x, y + 18); cout<<"                                                                                   ";
			gotoxy(x, y + 18);cout<<"Date of arrival at the local harbour \t: "<<date_of_arrival_at_the_local_harbour<<"                                            "<<endl;
			gotoxy(x, y + 20);cout<<"Ship number \t\t\t\t: "<<shipNumber<<endl;
			gotoxy(x, y + 22);	cout << "*********************************************************";
		}
		
};

class Supplies
{
private:
	vector<Local_Supply> Local;
	vector<International_Supply> International;

public:

	void showSupplies(int edit = 0)
	{
		gotoxy(90, 3 + 15 * edit);	cout << "***********************";
		gotoxy(90, 4 + 15 * edit);	cout << "       Supplies";
		gotoxy(90, 6 + 15 * edit);	cout << "***********************";
		int total = Local.size()+International.size();


		int columnlength01 = 0, columnlength02 = 0;
		if (total % 3 == 2)
		{
			columnlength01 = 1; columnlength02 = 1;
		}
		if (total % 3 == 1)
		{
			columnlength01 = 1;
		}
		columnlength01 += total / 3;
		columnlength02 += total / 3;
		int left = 0, middle = 0, right = 0;
		for (int i = 0; i < Local.size(); i++)
		{
				if (columnlength01-- > 0)
				{
					Local[i].showData(8, 10 + (left++) * 25 + 15 * edit);
				}
				else if (columnlength02-- > 0)
				{
					Local[i].showData(72, 10 + (middle++) * 25 + 15 * edit);
				}
				else
				{
					Local[i].showData(136, 10 + (right++) * 25 + 15 * edit);
				}
		}
		for (int i = 0; i < International.size(); i++)
		{
				if (columnlength01-- > 0)
				{
					International[i].showData(8, 10 + (left++) * 25 + 15 * edit);
				}
				else if (columnlength02-- > 0)
				{
					International[i].showData(72, 10 + (middle++) * 25 + 15 * edit);
				}
				else
				{
					International[i].showData(136, 10 + (right++) * 25 + 15 * edit);
				}
		}
	}

	void add_product_to_supplies()
	{		
		gotoxy(50, 6); cout << "If the supply is international enter I, if it is local enter L : ";
		char ch;
		gotoxy(120, 6); cin>>ch;	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (ch=='I')
		{
			International_Supply obj;
			obj.setData();
			International.push_back(obj);
			system("cls");
		}
		
		if (ch=='L')
		{
			Local_Supply obj;
			obj.setData();
			Local.push_back(obj);
			system("cls");
		}
	}

	void pass_supplies(string &Category , string &Name , float &Quantity )
	{
		showSupplies(1);
		
		gotoxy(20, 6); cout << "Enter the Category (Exactly as it is in the stocks) :";
		string category;
		gotoxy(100, 6); cin>>category;	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		Category=category;
		gotoxy(20, 8); cout << "Enter the Name (Exactly as it is in the stocks)     :";
		string name;
		gotoxy(100, 8); cin>>name;	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		Name=name;
		gotoxy(20, 10); cout << "Enter the quantity you want to pass                 :";
		float quantity;
		gotoxy(100, 10); cin>>quantity;	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		for(int i=0;i<Local.size();i++)
		{
			Local[i].remove_pending_goods(Category , Name , quantity);
		}
		for(int i=0;i<International.size();i++)
		{
			International[i].remove_pending_goods(Category , Name , quantity);
		}		
		Quantity=quantity;
		
		system("cls");
	}

};


class Staff
{
	private:
		string username, password, fullName, position, joinedDate;
		int positionValue;
		
	public:
		Staff(string Username = "", string Password = "", string FullName = "", string Position = "", int PositionValue = 0, string JoinedDate = "") : username(Username), password(Password), fullName(FullName), position(Position), positionValue(PositionValue), joinedDate(JoinedDate) {}
		
		void setData()
		{
			cout<<"Enter the full name : ";
			getline(cin,fullName);
			
			cout<<"Enter the joined date (DD/MM/YYYY) : ";
			getline(cin,joinedDate);
			
			cout<<"Enter the position : ";
			getline(cin,position);

			cout<<"\nEnter the username : ";
			getline(cin,username);
			
			cout<<"Enter a password for the account : ";
			getline(cin,password);
			
		//Assigining values for the positions
			
			if(position == "Owner")
				positionValue = 3;
				
			else if(position == "Manager")	
				positionValue = 2;
				
			else if(position == "Cashier")
				positionValue = 1;	
			
			else
				positionValue = 0;	
			
		}
		
		void showData()
		{
			cout<<"Name        : "<<fullName<<endl;
			cout<<"Username    : "<<username<<endl;
			cout<<"Position    : "<<position<<endl;
			cout<<"Joined date : "<<joinedDate<<endl;
			
		}
		
		string get_username()
		{
			return username;
		} 
		 
		string get_password()
		{
			return password;
		} 
		
		int get_positionValue()
		{
			return positionValue;
		}	
		
		string get_fullname()
		{
			return fullName;
		}
		 		 
};

/*
/////////////Transaction class is incomplete////////////////////////

class Transaction
{
	private:
		string name_of_the_cashier, customer;
		//item list array
		
	public:
		Transaction(string Name_of_the_cashier = "", string Customer = "") : name_of_the_cashier(Name_of_the_cashier), customer(Customer) {}
		
		void set_cashierName(string Name_of_the_cashier)
		{
			name_of_the_cashier = Name_of_the_cashier;
		}
		
		void setData()
		{
			cout<<"Enter the name of the customer : ";
			getline(cin,customer);
			
			//item details
		}
		
		void showData()
		{
			cout<<"Cashier  : "<<name_of_the_cashier<<endl;
			cout<<"Customer : "<<customer<<endl;
			//item details
		}
		
};

*/

//Interconnect
class Interconnect
{
	Stocks StockObject;
	Supplies SupplyObject;
	Staff StaffDetails[4];
	public:
		void Initiate()
		{
			StockObject.initiate_vectors();
				
			StaffDetails[0] = {"owner@coolMart", "1", "A.B.C owner", "Owner", 3, "01/01/2010"};
			StaffDetails[1] = {"manager@coolMart", "2", "A.B.C manager", "Manager", 2, "02/01/2010"};
			StaffDetails[2] = {"cashier@coolMart", "3", "A.B.C cashier", "Cashier", 1, "01/03/2010"};
			StaffDetails[3] = {"floorWorker@coolMart", "4", "A.B.C Perera", "Floor Worker", 0, "01/03/2010"};
			
		}	
		
		void mainProgramme()
		{
			while(1)
			{
				string username;
				string password;
				int position=-1, option=0, selection=0;
				char back;
				
				string Category;
				string Name; 
				float quantity;
				
				system("cls");
				
				gotoxy(85, 15); cout<<"Username : ";
				cin>>username;				
				gotoxy(85, 16); cout<<"Password : ";
				cin>>password;
				
				for(int i=0; i<4; i++)
					if(username==StaffDetails[i].get_username() && password==StaffDetails[i].get_password() )
						position = StaffDetails[i].get_positionValue();

				if(position==-1)
				{
					gotoxy(80, 18); cout<<"Access denied......\n\n";
					break;	
				}

				while(1)
				{
					system("cls");
					
					gotoxy(66, 11); cout<<"| WELCOME TO COOL MART INVENTORY MANAGEMENT SYSTEM |";
					gotoxy(65, 12);cout<<"******************************************************";
					
					if(position==3||position==2||position==1)
					{
						gotoxy(85, 15); cout<<"1.Stock";						
					}

												
					if(position==3||position==2||position==0)
					{
						gotoxy(85, 17);	cout<<"2.Supply";
					}
											
					if(position==3||position==2)
					{
						gotoxy(85, 19); cout<<"3.Staff";
					}
																			
					gotoxy(85, 21); cout<<"4.Exit";
											
					gotoxy(80, 24); cout<<"Option : ";
					cin>>option;
										
					if(option==1 && (position==3||position==2||position==1) )
					{
						while(1)
						{		
							system("cls");
											
							gotoxy(87, 12); cout<<"| STOCK |";
					        gotoxy(84, 13); cout<<"***************";
							gotoxy(85, 15); cout<<"1.Show stock";
							gotoxy(85, 17); cout<<"2.Stock down";
							gotoxy(85, 19); cout<<"3.Add a new category";
							gotoxy(85, 21); cout<<"4.Add a new product";
							gotoxy(85, 23); cout<<"5.Go to main menu";										
							gotoxy(85, 25); cout<<"6.Exit";
							
							gotoxy(80, 28); cout<<"Selection : ";
							cin>>selection;	
							
							if(selection==5)
								break;
															
							while(1)
							{
								system("cls");
								
								if(selection==1)
									StockObject.showstock(0);
								
								else if(selection==2)
								{   
									while(1)
									{	
								 		system("cls");
										 									
										gotoxy(30, 10); cout<<"Press 'd' to stock down or Press space to go back...";
								 		back = getche();
								 		
								 		system("cls");
									
										if(back == ' ')
											break;
											
										else
										{
											gotoxy(94, 1); cout<<"| Stock down |";
											gotoxy(85, 2); cout<<"********************************";
											
											StockObject.stock_down(Category, Name, quantity);																									
											StockObject.stock_up_down(Category, Name, quantity, 'd');
										}																																								
									}                         	
								}
								else if((position==3||position==2) && selection==3)
								{
									string tempCategory;
									char tempMeasure;
									bool tempBrandedStatus;
									
									while(1)
									{
										system("cls");
												 									
										gotoxy(30, 10); cout<<"Press 'a' to add a new category or Press space to go back...";
										back = getche();
										 		
										system("cls");
											
										if(back == ' ')
											break;											
										
										gotoxy(20, 6); cout << "Enter the name of the new category                                       :";
										gotoxy(100, 6); cin>>tempCategory;	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
										
										gotoxy(20, 8); cout << "Enter the type of measurement (g-grams, n-count)                         :";
										gotoxy(100, 8); cin>>tempMeasure;	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							
										gotoxy(20, 10); cout << "Enter whether the products are branded or not (branded-1 and unbranded-0) :";
										gotoxy(100, 10); cin>>tempBrandedStatus;	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																			
										StockObject.add_category(tempCategory, tempMeasure, tempBrandedStatus);										
									}

								}
								else if((position==3||position==2) && selection==4)
								{
									while(1)
									{
										system("cls");
												 									
										gotoxy(30, 10); cout<<"Press 'a' to add a new product or Press space to go back...";
										back = getche();
										 		
										system("cls");
											
										if(back == ' ')
											break;	
																				
										StockObject.add_product();										
									}

								}
									
								else if(selection==6)
									exit(0);
									
								else	
								{
									gotoxy(80, 18); cout<<"Access denied......\n\n";									
								}

	
								gotoxy(0, 0); cout<<"Press space to go to the menu...";
							 	back = getche();
								
								if(back == ' ')
									break;
							}
						}
						
					}
					else if(option==2 && (position==3||position==2||position==0 ))
					{
						while(1)
						{
							system("cls");
							
							gotoxy(87, 12); cout<<"| SUPPLY |";
					        gotoxy(82, 13); cout<<"********************";								
							gotoxy(85, 15); cout<<"1.Show supply";
							gotoxy(85, 17); cout<<"2.Add to stock";
							gotoxy(85, 19); cout<<"3.Add a supply";
							gotoxy(85, 21); cout<<"4.Go to main menu";							
							gotoxy(85, 23); cout<<"5.Exit";
								
							gotoxy(80, 26); cout<<"Selection : ";
							cin>>selection;
							
							if(selection==4)
								break;
								
							while(1)
							{
								system("cls");							
																	
								if(selection==1)
									SupplyObject.showSupplies(0);
								
								else if(selection==2)
								{
									while(1)
									{
										system("cls");
												 									
										gotoxy(30, 10); cout<<"Press 'u' to stock up or Press space to go back...";
										back = getche();
										 		
										system("cls");
											
										if(back == ' ')
											break;								
										
										gotoxy(93, 1); cout<<"| Add to stock |";
										gotoxy(85, 2);	cout<<"********************************";
															
										SupplyObject.pass_supplies(Category,Name,quantity);
										StockObject.stock_up_down(Category,Name,quantity,'u');									
									}
									
								}
								else if(selection==3)
								{
									while(1)
									{
										system("cls");
												 									
										gotoxy(30, 10); cout<<"Press 'a' to add a supply or Press space to go back...";
										back = getche();
										 		
										system("cls");
											
										if(back == ' ')
											break;
											
										gotoxy(93, 1); cout<<"| Add a supply |";
										gotoxy(85, 2);	cout<<"********************************";										
										SupplyObject.add_product_to_supplies();										
									}
								}
								else if(selection==5)
									exit(0);
									
								else
								{
									gotoxy(80, 28); cout<<"Error!!!!";
									break;
								}	
									
								gotoxy(0, 0); cout<<"Press space to go to the menu...";
							 	back = getche();
								
								if(back == ' ')
									break;												
							}	
						}
						
					}					
					else if(option==3 && (position==3||position==2))
					{
						system("cls");
												
						while(1)
						{
							cout<<endl;
																										
						 	for(int i=0; i<4; i++)
							{
								StaffDetails[i].showData();
								cout<<endl;							
							}
		
							cout<<"\n\nPress space to go back...";
							back = getche();
								
							if(back == ' ')
								break;							
						}
		
					}
					else
						exit(0);
																
				}
			}				
		}	
};

int main()
{
	Interconnect ob01;
	
	ob01.Initiate();
	ob01.mainProgramme();

	return 0;		
}





