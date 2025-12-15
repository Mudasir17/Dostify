#include <iostream>
using namespace std;

class Dpost{
public:
	int id; 
	string  post;
    Dpost *next;
	Dpost *pre;
};
class notifications{
public:
	string notification;
	notifications * next;
};
notifications *rear=NULL,*front=NULL;
void enqueue(string s){
	notifications *newnode=new notifications;
	newnode->notification=s;
	newnode->next=NULL;
	if(rear==NULL){
		rear=newnode;
		front=newnode;
	}else{
	rear->next=newnode;
	rear=rear->next;}
}
void display_notifications(){
	notifications *temp=front;
	cout<<"============================================================"<<endl;
	cout<<"                     Notifications                          "<<endl;
	cout<<"============================================================"<<endl;
	
	while(temp!=NULL){
		cout<<temp->notification<<endl;
		temp=temp->next;
	}	
}
Dpost *head=NULL;
void insert_post(int i,string p){
	Dpost *newnode= new Dpost;
	newnode->id=i;
	newnode->post= to_string(i)+string(". ")+p;
	newnode->next=head;
	newnode->pre=NULL;
	if(head!=NULL){
		head->pre=newnode;
	}
	head=newnode;
}
void display_post(){
	Dpost *temp= head;
	while(temp!=NULL){
		cout<<temp->post<<endl;
		temp=temp->next;
	}
}
void delete_post(int pos){
	
//	if(pos==1){
//		Dpost *temp=head;
//		cout<<"Are you sure to delete this:(yes/no) "<<endl;
//		cout<<head->post<<endl;
//		string choice;
//		cin.ignore();
//		getline(cin,choice);
//		if(choice=="yes"){
//		head=head->next;
//		delete temp;	
//		cout<<"the post has successfully deleted"<<endl;
//		}
//		else
//			cout<<"the post not deleted"<<endl;
//	}
	cout<<"Are you sure to delete this:(yes/no) "<<endl;
	Dpost*p=head;
	while(p->id!=pos){
		p=p->next;
	}
	cout<<p->post<<endl;
	string choic;
	cin.ignore();
	getline(cin,choic);
	if(choic=="yes"){
		if(p->pre==NULL){
			Dpost *temp=head;
			head=head->next;
			delete temp;
			cout<<"Post successfully deleted"<<endl;
			string v="You deleted the post";
			enqueue(v);
		}
		else if(p->next==NULL){
			p->pre->next=NULL;
			delete p;
			cout<<"Post successfully deleted"<<endl;
			string v="You deleted the post";
			enqueue(v);
		}
		else{
		Dpost *del=p;
		p->next->pre=p->pre;
		p->pre->next=p->next;
		delete del;
	cout<<"the post has successfully deleted"<<endl;}
	}
	else 
		cout<<"Post not deleted"<<endl;
}

int main_old(){
	int n{0},i{0};
	while(n!=5){
	std::cout << "====================== Dostify Menu =======================" << std::endl;
	std::cout << "|                                                         |" << std::endl;
	std::cout << "| 1. Share a Post: Spread your thoughts with the world!   |" << std::endl;
	std::cout << "| 2. View Posts: Check out what others are sharing.       |" << std::endl;
	std::cout << "| 3. Delete a Post: Remove something from your timeline.  |" << std::endl;
	std::cout << "| 4. Notifications: want to see the Notifications.        |" << std::endl;
	std::cout << "| 5. Exit : Want to quit.                                 |" << std::endl;
	std::cout << "|                                                         |" << std::endl;
	std::cout << "===========================================================" << std::endl;
	std::cout << "Enter your choice (1-5): ";
    
	int post_id;
	string s,n1,n2;
	cin>>n;
	cin.ignore();
	switch (n) {
	case 1:
		cout<<"How are feeling today....!"<<endl;
		getline(cin,s);
		i++;
		insert_post(i,s);
		n1="you added post successfully ";
		enqueue(n1);
		break;
	case 2:
		display_post();
		break;
	case 3:
		cout<<"which post you want to delete"<<endl;
		display_post();
		cin>>post_id;
		delete_post(post_id);
		break;
	case 4:
	    display_notifications();
		break;
	}
	}
}
