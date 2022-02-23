#include<iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int skip = 1;

enum Family {TTL, BiCMOS, CMOS};

enum Package {SSOP, SOIC, DIP, CFP, LCCC, SO};

class SNx4xx{
	private:
		string Part_Number;
		string Part_Name;
		string Description;
		Family family;
		Package package;
		float Vcc[4];
		float Vil;
		float Vih;
		
	public:
		
		SNx4xx(){
			Vcc[4] = {0.0};
			Vil = 0.0;
			Vih = 0.0;
		}
		
		//getter and setter for part number
		string getPart_Number(){
			return Part_Number;
		}
		void setPart_Number(string part_number){
			Part_Number = part_number;
		}
		
		//getter and setter for part name
		string getPart_Name(){
			return Part_Name;
		}
		void setPart_Name(string part_name){
			Part_Name = part_name;
		}
		
		//getter and setter for description
		string getDescription(){
			return Description;
		}
		void setDescription(string description){
			Description = description;
		}
		
		//getter and setter for Family (enum)
		Family getFamily(){
			return family;
		}
		void setFamily(Family f){
			family = f;
		}
		
		//getter and setter for Package (enum)
		Package getPackage(){
			return package;
		}
		void setPackage(Package p){
			package = p;
		}
		
		//getter and setter for Vcc
		float * getVcc(){
			return Vcc;
		}
		void setVcc(float vcc[]){
			for(int i=0; i<4; i++){
				Vcc[i] = vcc[i];
			}
		}
		
		//getter and setter for Vil
		float getVil(){
			return Vil;
		}
		void setVil(float vil){
			Vil = vil;
		}
		
		//getter and setter for Vih
		float getVih(){
			return Vih;
		}
		void setVih(float vih){
			Vih = vih;
		}
		
		//load file infile.part
		bool load(){
			ifstream indata;
			int f,p;
			float v;
			indata.open("infile.part");
			
			//if no data present.
			if(!indata) { 
		      cout << "Error: file could not be opened" << endl;
		      return false;
			}
			
			//else read the file and load the data.
			
			//for skipping lines.
			for(int i=1; i<skip; i++){
				string line;
				for(int j=0; j<8; j++){
					getline(indata,line);
				}
			}
			
	   		getline(indata,Part_Number);
	   		getline(indata,Part_Name);
	   		getline(indata,Description);
	   		indata >> f;
	   		family = (Family)(f);
	   		indata >> p;
	   		package = (Package)(p);
	   		for(int i=0; i<4; i++){
	   			indata >> v;
	   			Vcc[i] = v;
			}
			indata >> v;
			Vil = v;
			indata >> v;
			Vih = v;
		   	
		   	//closing the file.
			indata.close();
			skip++;
			
			return true;
		}
		
		//save file outfile.part.
		void save(){
			ofstream outfile;
   			outfile.open("outfile.part",ios_base::app);
   			//writing data to file.
   			outfile << Part_Number << endl;
   			outfile << Part_Name << endl;
   			outfile << Description << endl;
   			outfile << family << endl;
   			outfile << package << endl;
   			for(int i=0; i<4; i++){
			   outfile << Vcc[i]<<" ";
			}
			outfile << endl;
   			outfile << Vil << endl;
   			outfile << Vih << endl;
   			outfile.close();
		}
		
		//print method 
		void print(){
			cout<<"----------------------------------------------"<<endl;
			cout<<Part_Number<<" "<<Part_Name<<endl<<endl;
			cout<<Description<<endl;
			cout<<endl;
			switch(family){
				case 0:
					cout<<"TTL";
					break;
				case 1:
					cout<<"BiCMOS";
					break;
				case 2:
					cout<<"CMOS";
					break;
				
			}
			switch(package){
				case 0:
					cout<<" SSOP";
					break;
				case 1:
					cout<<" SOIC";
					break;
				case 2:
					cout<<" DIP";
					break;
				case 3:
					cout<<" CFP";
					break;
				case 4:
					cout<<" LCCC";
					break;
				case 5:
					cout<<" SO";
					break;
			}
			cout<<endl;
			cout<<"VCC: ";
			for(int i=0; i<3; i++){
				cout<<fixed<<setprecision(1)<<Vcc[i]<<"V, ";
			}
			cout<<fixed<<setprecision(1)<<Vcc[3]<<"V"<<endl;
			cout<<fixed<<setprecision(1)<<"Vil = "<<Vil<<"V "<<"Vih = "<<Vih<<"V"<<endl;
		}
	
};

void checkLoad(bool fileLoad){
	if(fileLoad){
		cout<<"The file data is loaded."<<endl;
	}else{
		cout<<"The file data is not loaded."<<endl;
	}
}

int main(){
	SNx4xx obj1, obj2;
	bool fileLoad = obj1.load();
//	checkLoad(fileLoad);
	obj1.save();
	obj1.print();
	
	fileLoad = obj2.load();
//	checkLoad(fileLoad);
	obj2.save();
	obj2.print();
	
	//array type of class.
	SNx4xx arr[4];
	
	//enum objects.
	Family f;
	Package p;
	float Vcc_arr[4][4] = {
		{4.0,3.2,6.7,8.1},
		{3.0,2.2,1.7,9.1},
		{5.0,4.2,3.7,2.1},
		{1.0,2.2,3.7,5.1}
	};
	//some values setting using Setter.
	arr[0].setPart_Number("SN74LS02TH");
	arr[0].setPart_Name("Quadruple 2-input NOR gate");
	arr[0].setDescription("The SNx4xx02 devices contain four independent, 2-input NOR gates. The devices perform the Boolean function Y = not(A+B) or Y = not(A).not(B) in positive logic.");
	arr[0].setFamily((Family)1);
	arr[0].setPackage((Package)2);
	arr[0].setVcc(Vcc_arr[0]);
	arr[0].setVil(0.5);
	arr[0].setVih(0.9);
	
	
	arr[1].setPart_Number("SN74LS02YU");
	arr[1].setPart_Name("Quadruple 2-input NOR gate");
	arr[1].setDescription("The SNx4xx02 devices contain four independent, 2-input NOR gates. The devices perform the Boolean function Y = not(A+B) or Y = not(A).not(B) in positive logic.");
	arr[1].setFamily((Family)2);
	arr[1].setPackage((Package)1);
	arr[1].setVcc(Vcc_arr[1]);
	arr[1].setVil(1.1);
	arr[1].setVih(3.1);
	
	arr[2].setPart_Number("SN74LS02IO");
	arr[2].setPart_Name("Quadruple 2-input NOR gate");
	arr[2].setDescription("The SNx4xx02 devices contain four independent, 2-input NOR gates. The devices perform the Boolean function Y = not(A+B) or Y = not(A).not(B) in positive logic.");
	arr[2].setFamily((Family)0);
	arr[2].setPackage((Package)5);
	arr[2].setVcc(Vcc_arr[2]);
	arr[2].setVil(0.2);
	arr[2].setVih(0.5);
	
	arr[3].setPart_Number("SN74LS02RE");
	arr[3].setPart_Name("Quadruple 2-input NOR gate");
	arr[3].setDescription("The SNx4xx02 devices contain four independent, 2-input NOR gates. The devices perform the Boolean function Y = not(A+B) or Y = not(A).not(B) in positive logic.");
	arr[3].setFamily((Family)0);
	arr[3].setPackage((Package)3);
	arr[3].setVcc(Vcc_arr[3]);
	arr[3].setVil(0.4);
	arr[3].setVih(1.7);
	
	cout<<"\n********************** data using getter and setter to array ***************\n\n";
	
	for(int i=0; i<4; i++){
		arr[i].print();
		arr[i].save();
	}
	
}
