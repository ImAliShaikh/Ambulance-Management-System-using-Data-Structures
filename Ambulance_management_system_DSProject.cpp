#include<iostream>
#include <bits/stdc++.h> 
#include <conio.h>
#define V 11
#include<string>
#define INF 500   //max dist for graph


//USER GUIDE:
//Use a full screen console to display data properly.
//Initializing data is a must for the user.(Option 1 on main menu) 
//Names must be enter carefully as they are case sensitive.
//Instructions must be carefully read before entering any input type.
//Source and Destination must be provided before using the shortest path funtion.
//DoneWithPatients File is created which represents the patients that are dealth with

using namespace std; 

int eleCount=0; //number of keys we wants to have

string areas_name[11]={"Gulshan-i-Iqbal", "Saddar(DHA,Clifton)", "North-Nazimabad", "Malir", "Jamshed-Town", "North-Karachi",
	             "Orangi-Town", "Gulberg", "Lyari", "Liaquatabad", "Shah-Faisal"}; //areas to be mapped on the graph
struct node
{
	    string name;
		string cnic;
		string area;
		int age;
		string pno;
	    struct node *next;

};

struct hashr { // structure for hash table
        struct node *head;
        int count;
};

struct hashr *hashTable = NULL; 

struct node* createNode(string n, int age, string cn, string pnum, string ar){ //node initialization
	    node *t=new node;
		t->name=n;
		t->cnic=cn;
		t->age=age;
		t->next=NULL;
		t->area=ar;
		t->pno=pnum;
		return t;
}


void insertToHash(string n, int age, string cn, string pnum, string ar){ //insert data of an individual into hash table
        int hashIndex = age % eleCount;
        struct node *newnode =  createNode( n, age, cn, pnum, ar);
        /* head of list for the bucket with index "hashIndex" */
        if (!hashTable[hashIndex].head) {
                hashTable[hashIndex].head = newnode;
                hashTable[hashIndex].count = 1;
                return;
        }
        /* adding new node to the list */
        newnode->next = (hashTable[hashIndex].head);
        /*
         * update the head of the list and no of
         * nodes in the current bucket
         */
        hashTable[hashIndex].head = newnode;
        hashTable[hashIndex].count++;
        return;
}

void deleteFromHash(int age, string name){ //delete data of an individual at will
        /* find the bucket using hash index */
        int hashIndex = age % eleCount, flag = 0;
        struct node *temp, *myNode;
        /* get the list head from current bucket */
        myNode = hashTable[hashIndex].head;
        if (!myNode) {
                cout<<"Given data is not present in hash Table!!\n";
                return;
        }
        temp = myNode;
        while (myNode != NULL) {
                /* delete the node with given key */
                if (myNode->age==age && myNode->name==name) {
                        flag = 1;
                        if (myNode == hashTable[hashIndex].head)
                                hashTable[hashIndex].head = myNode->next;
                        else
                                temp->next = myNode->next;

                        hashTable[hashIndex].count--;
                        free(myNode);
                        break;
                }
                temp = myNode;
                myNode = myNode->next;
        }
        if (flag)
                cout<<"Data deleted successfully!\n";
        else
                cout<<"Given data is not present in directory!!!!\n";
        return;
}

node* searchInHash(int age, string name){ //search data of an individual in hash table
        int hashIndex = age % eleCount, flag = 0;
        struct node *myNode;
        myNode = hashTable[hashIndex].head;
        if (!myNode) {
                cout<<"Searched element UNAVAILABLE in directory!\n";
                return NULL;
        }
        while (myNode != NULL) {
                if (myNode->age == age && myNode->name==name) {
                	    cout<<"========================================================================================================\n"; 
                        cout<<"P.NO                        Cnic                      Age         Name                        Area Name"<<endl;
                        cout<<"========================================================================================================\n";
                        cout<<myNode->pno<<"               "<<myNode->cnic<<"            "<<myNode->age<<"         "<<myNode->name<<"                "<<myNode->area<<endl;
                        flag = 1;
                        return myNode;
                        break;
                }
                myNode = myNode->next;
        }
        if (!flag)
                cout<<"Searched element UNAVAILABLE in directory!\n";
        return NULL;
}

void display() {  //display hash table w.r.t keys
        struct node *myNode;
        int i;
        for (i=0; i < eleCount; i++) {
                if (hashTable[i].count == 0)
                        continue;
                myNode = hashTable[i].head;
                if (!myNode)
                        continue;
                printf("\nData at index %d in Hash Table:\n", i);
                cout<<"========================================================================================================\n"; 
                cout<<"P.NO                        Cnic                      Age         Name                        Area Name"<<endl;
                cout<<"========================================================================================================\n";
                while (myNode != NULL) {
                	cout<<myNode->pno<<"               "<<myNode->cnic<<"            "<<myNode->age<<"         "<<myNode->name<<"                "<<myNode->area<<endl;
                        myNode = myNode->next;
                }
        }
        return;
}

node* selectPatient(int age) {  //display hash table w.r.t keys
        if(age<=0 && age>83){
        	cout<<"Enter Age: ";
        	cin>>age;
		}
		else{
                struct node *myNode;
                if (hashTable[age].count == 0)
                        cout<<"Age Doesn't Exist In Directory!.";
                myNode = hashTable[age].head;
                if (!myNode)
                        cout<<"Age Doesn't Exist In Directory!.";
                        
                cout<<"Data With Age "<<age<<": "<<endl;
                cout<<"========================================================================================================\n"; 
                cout<<"P.NO                        Cnic                      Age         Name                        Area Name"<<endl;
                cout<<"========================================================================================================\n";
                while (myNode != NULL) {
                	cout<<myNode->pno<<"               "<<myNode->cnic<<"            "<<myNode->age<<"         "<<myNode->name<<"                "<<myNode->area<<endl;
                        myNode = myNode->next;
                }
                string name;
                cout<<endl<<endl<<endl<<"Enter Name And Age Of The Particular Patient You Want To Visit First: (From The Above List)"<<endl;
                cout<<"Name: ";
                cin>>name;
                cout<<endl<<endl<<endl<<"Following Patient Is Set As The Priority Pateint: "<<endl;
                node *destination_node = searchInHash(age, name);
		        return destination_node;
	}
	return NULL;
}


struct Node{      //node info for every box of 2D-Array
		string from_area;
		string to_area;
		int dist;
}graph[V][V];  //adjacency matrix


int shortestPath(int source, int destination, int visited[], Node matrix[][V])  //modified version of depth first search
{
	    if (source==destination){ //recursive step
	        return 0; 
	    }
	    
	    visited[source]=1; //marking the source node as visited 
	    int minCost = INF;
	    
	    for (int i=0; i<V; i++){ //traversing through all adjacent nodes of source
	        if (matrix[source][i].dist!=INF && !visited[i]) { 
	             
	            int curr;
	            //cout<<endl<<matrix[source][i].from_area<<" to "<<matrix[source][i].to_area<<": "<<matrix[source][i].dist<<"KM's"<<endl;
				curr=shortestPath(i, destination, visited, graph); 
	            
	        if (curr<INF) {  //destination reached
	                minCost=min(minCost, matrix[source][i].dist+curr); //minimum cost path
	            } 
	        } 
	    } 
//	    visited[source]=0;
	    return minCost; 
} 

void assignProperties(){
	    
		for(int i=0; i<11; i++){ //assigning from_areas
	      
	        for(int j=0; j<11; j++){
	      	
	      	graph[i][j].from_area=areas_name[i];
	      }
	      
	    }            
	    
	    int check=0;  
	   	for(int i=0; i<11; i++){ //assigning to_areas
	      
	      for(int j=0, k=0; j<11; j++, k++){
	      	if(j!=check){
	      	graph[i][j].to_area=areas_name[j];
	        }
	      }
	      check++;
	    }     
		 

      	int Matrix[11][11] = {{INF, 4, INF, INF, INF, INF, INF, 8, INF, 8, INF}, //giving weights/distances to 2D array
							   {4, INF, 8, INF, INF, INF, INF, 11, INF, 3, INF}, 
							   {INF, 8, INF, 7, INF, 4, INF, INF, 2, INF, 9}, 
							   {INF, INF, 7, INF, 9, 14, INF, INF, INF, 10, INF}, 
							   {INF, INF, INF, 9, INF, 10, INF, INF, INF, INF, 3}, 
						       {INF, INF, 4, INF, 10, INF, 2, INF, INF, INF, 6}, 
							   {INF, INF, INF, 14, INF, 2, INF, INF, 6, 5, 2}, 
							   {8, 11, INF, INF, INF, INF, 1, INF, 7, 1, INF}, 
							   {INF, INF, 2, INF, INF, INF, 6, 7, INF, INF, 3},
							   {8, 3, INF, 10, INF, INF, 5, 1, INF, INF, 1},
							   {INF, INF, 9, INF, 3, 6, 2, INF, 3, 1, INF}
							}; 
		for(int i=0; i<11; i++){ //copying data from 2D array to adjacency matrix
	      
	      for(int j=0; j<11; j++){
                graph[i][j].dist=Matrix[i][j];
	      }	
     	}

}

int placingAmbulance(){ //place ambulance at area of user's will
	int opt,source_location;
	cout<<"===================================================\n";             
	cout<<"Choose Location for placing the Ambulance: "<<endl;
	cout<<"===================================================\n";
	for(int i=0;i<11; i++){
		cout<<i+1<<": "<<areas_name[i]<<endl;
	}
	cout<<"Enter Choice: ";
	cin>>opt;
	source_location=opt-1;
	return source_location;
}

int assignDestination(string s){ //assign destination using area's name of patient
	int destination_location;
	for(int i=0, j=0; i<11; i++){
		if(graph[i][j].from_area == s){       
			destination_location = i;
		}
	}
	return destination_location;
}

void showDistances(){
	int check=0;
    cout<<"=====================================================================\n"; //display area to area distance
    cout<<"Distance In Kilometeres      "<<"Locations"<<endl;
    cout<<"=====================================================================\n";
    for(int i=0; i<11; i++){ // print area to area distances with weights in kilometeres
      
      for(int j=0; j<11; j++){
          if(check!=j){
            
            if(graph[i][j].dist!=INF){
                cout<<"|"<<graph[i][j].dist<<"|"<<"\t\t\t     "<<graph[i][j].from_area<<" - "<<graph[i][j].to_area<<endl;
		    }
		    
		    else{
		    	cout<<"|NR|\t\t\t     "<<graph[i][j].from_area<<" - "<<graph[i][j].to_area<<endl; //No Route
			}
          }
      }
      check++;
      cout<<endl;
    }
}




void password_security(){ //password protected program
		char pwd[]="1234";
		char user_pass[4];
		string n;
		cout<<"\t=======================================================================================================\n";	
	    cout<<"\t\t\t\t\tCOVID'19 AMBULANCE SERVICE SYSTEM\n";
	    cout<<"\t=======================================================================================================\n\n";
		cout<<endl<<endl<<endl<<endl<<endl<<endl;
		cout<<"                                      ==========================================\n";	
		cout<<"                                                  Enter User Name : ";	
		cin>>n;
		cout<<"                                      ==========================================\n";
		cout<<endl<<endl;
		cout<<"                                      ==========================================\n";	
		cout<<"                                                  Enter Password : ";	//2001
		for(int i=0;i<4;i++){    
			user_pass[i]=getch();
			cout<<'*';
		}
		int i=0,check=0;
		while(i<4){
			if(user_pass[i]==pwd[i]){
				check++;
			}
			i++;
		}
		if(check!=4 || n!= "Murtaza"){
			exit(1);
		}
		cout<<endl;
		cout<<"                                      ==========================================\n";
		cout<<endl<<endl<<endl;
}



int main(){
    int choice, age;
    string name, pno, cnic, area;
    
	ifstream pcnic,pname,page,pphno,areas;
	
	pcnic.open("cnic.txt");
	pname.open("name.txt");
	pphno.open("phonenumbers.txt");
	page.open("age.txt");
	areas.open("area.txt");
	
	pcnic>>cnic;
	pname>>name;
	pphno>>pno;
	page>>age;
	areas>>area;
	

    eleCount=84;
        /* create hash table with "eleCount" no of buckets */
    hashTable = (struct hashr *)calloc(eleCount, sizeof (struct hashr)); //dynamic allocation
    
    password_security();
    

    while (1) {
    	        page1:
                system("cls");
	            cout<<"\n\n\n\n\n\n\n\n=================================================================\n";	
	            cout<<"Enter 1 For Initialization Of Data From File Directory.(MUST)\n";
	            cout<<"=================================================================\n\n";
	            cout<<"Enter 2 To Delete A Patient's Data.\n"; //incase the patient cures somehow
	            cout<<"=======================================\n\n";
	            cout<<"Enter 3 To Search A Patient's Data.\n"; //searching a particular individual/maybe out of priority
	            cout<<"=======================================\n\n";
	            cout<<"Enter 4 to Display Ordered Data.\n"; //Display the whole data set (ordered)
	            cout<<"=======================================\n\n";
	            cout<<"Enter 5 For Ambulance Access.\n";       
	            cout<<"=======================================\n\n";
	            cout<<"Enter 6 to Exit.\n";
	            cout<<"=======================================\n\n";
                cout<<"Enter Choice: ";
                cin>>choice;
                switch(choice) {
                        case 1:
                                system("cls");
                                cout<<"========================================================================================================\n"; 
                                cout<<"P.NO                        Cnic                      Age         Name                        Area Name"<<endl;
                                cout<<"========================================================================================================\n";
                        	    while(!pcnic.eof() )
	                            {	
		                          cout<<pno<<"               "<<cnic<<"            "<<age<<"         "<<name<<"                "<<area<<endl;
	                        	  pcnic>>cnic;
	                              pphno>>pno;
	                              pname>>name;
	                              page>>age;
	                              areas>>area;
	                              insertToHash(name , age, cnic, pno, area);
	                        
	                            }
                                system("pause");
                                break;

                        case 2:
                        	    system("cls");
                                cout<<"Enter the age to perform deletion: ";
                                cin>>age;
                                cout<<"Enter name: ";
                                cin>>name;
                                /* delete node with "age" from hash table */
                                deleteFromHash(age, name);
                                system("pause");
                                break;

                        case 3:
                                system("cls");
                                cout<<"=====================\n";
                                cout<<"Enter Age To Search: ";
                                cin>>age;
                                cout<<"=====================\n";
                                cout<<"Enter Name: ";
                                cin>>name;
                                cout<<"=====================\n";
                                searchInHash(age,name);
                                system("pause");
                                break;
                        case 4:
                        	    system("cls");
                                display();
                                system("pause");
                                break;
                        case 5:{
		                        assignProperties(); //assign properties to the graph
		                        int source=INF, destination=INF;
		                        node *destination_node;
		                        int visited[V]={0};
                                visited[source]=1; 
                                page2:
                                system("cls");
                               	cout<<"\n\n\n\n\n\n\n\n================================================================\n\n";	
	                            cout<<"Enter 1 To View Routes And Distances Between Areas.\n\n";
	    	 					cout<<"================================================================\n\n";
						    	cout<<"Enter 2 For Placing/Replace Ambulance At A Source/Starting Location.\n\n"; 
							    cout<<"================================================================\n\n";
						        cout<<"Enter 3 To Select Priority Pateint (Assigning Destination Location).\n\n";
							    cout<<"================================================================\n\n";
						    	cout<<"Enter 4 To View The Shortest Route In Reaching The Priority Patient.\n\n";  
							    cout<<"================================================================\n\n";
							    cout<<"Enter 5 To View The Current Pateint And Ambulance's Location.\n\n";  
							    cout<<"================================================================\n\n";
							    cout<<"Enter 6 To Return To Main.\n\n";
							    cout<<"================================================================\n\n";
						        cout<<"Enter Choice: ";
				                cin>>choice;	
				            switch(choice){
								case 1:{
                                  		system("cls");
							    		showDistances(); //display area to area distances
							    		system("pause");
							    		goto page2;
							    		break;
							    	}
						    		
						    	case 2:
							    		system("cls");
							    		source = placingAmbulance(); //return a source point for ambulance to start the journey 
							    		system("pause");
							    		goto page2;
							    		break;
				 
				                        
	    			            case 3:
	    			            	    system("cls");
							    		cout<<"Enter Age You Want To Prioritize: ";
							    		cin>>age;
							    		destination_node=selectPatient(age); //A node to save priority patient's information
							    		destination = assignDestination(destination_node->area);
							    		system("pause");
							    		goto page2;
							    		break;
							    		
						        case 4: {
                                        system("cls");
                                        if(source!=INF && destination!=INF){ //source and destination must be initialized
									    		cout<<"============================================\n";
								                cout<<"Possible Routes For The Ambulance"<<endl;
								                cout<<"============================================\n";
									                    
								                cout<<"=====================================================================================\n";
								                cout<<endl<<endl<<endl<<endl<<"Shortest Route From "<<graph[source][0].from_area<< " To "<<graph[destination][0].from_area<<" is : "<<shortestPath(source, destination, visited, graph)<<" KM's"<<endl;
								                cout<<"=====================================================================================\n";
								                cout<<"\n\n\n\n\n===================================================\n";          
								                cout<<endl<<endl<<"Enter 1 for DELETING this Patient's Data: ";
								                cin>>choice;
								                cout<<"===================================================\n";  
								                if(choice==1){
								                	ofstream myfile;
                                                    myfile.open ("DoneWithPatients.txt",ios::app);
								                	myfile<<destination_node->pno<<"               "<<destination_node->cnic<<"            "<<destination_node->age<<"         "<<destination_node->name<<"                "<<destination_node->area<<endl; 
								                    deleteFromHash(destination_node->age, destination_node->name); //delete data after ambulance picks that individual
								                    destination=500;
												}
												else if(choice == 0)
												{
													cout<<"Not DELETED!!!!!!!"<<endl<<endl;
												}
						                }
						                else{
						               	   cout<<"One of soruce or destination is not set by the user!!!"<<endl;
									    }
						                system("pause");
						                goto page2;
						                break;
							    	}
												
                                case 5:
                                	   system("cls");
                                	   if(source!=INF && destination!=INF){ //source and destination must be initialized
	                                	   cout<<"============================================\n";
							               cout<<"Current Source Location / Ambulance's Location: "<<graph[source][source].from_area<<endl;
							               cout<<"============================================\n";
							               cout<<endl<<endl<<endl;
							               cout<<"============================================\n";
							               cout<<"Current Destination Location / Patient's Location: "<<graph[destination][destination].from_area<<endl;
							               cout<<"============================================\n";
						               }
						               else{
						               	   cout<<"One of soruce or destination is not set by the user!!!"<<endl;
									   }
                                	   system("pause");
                                	   goto page2;
						                break;
	    		       			case 6:
					                    goto page1;
								        break;	

                                default:
		                        	    system("cls");
		                        	    cout<<"=======================================\n";
		                                cout<<"U have entered wrong option!!\n";
		                                cout<<"=======================================\n";
		                                system("pause");
		                                goto page2;
		                                break;
	    		           }
					}
                        case 6:{
                                exit(0);
                            }
                        default:
                        	    system("cls");
                        	    cout<<"=======================================\n";
                                cout<<"U have entered wrong option!!\n";
                                cout<<"=======================================\n";
                                system("pause");
                                break;
                }
        }
        return 0;
    }
