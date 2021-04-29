#include<iostream>
using namespace std;
class inf
{
    public:
    bool a;
    int b;
    inf()
    {
        a=true;
        b=0;
    }
};

class node
{
    public:
    int info;
    node *next;
    node(int el,node* ptr2=NULL)
    {
        info=el;
        next=ptr2;
    }
};

class slist
{
    private:
    node *head,*tail;
    public:
    slist()
    {
        head=tail=NULL;
    }
    ~slist();
    bool isempty()
    {
        return (head==NULL);
    }
    void addtotail(int);
    void display();
    void deletenode(int);
    void breadthFirst(slist b[],inf c[],int i);
};

void slist::addtotail(int el)
{
    if(tail!=NULL)
    {
        tail->next=new node(el);
        tail=tail->next;
    }
    else
        head=tail=new node(el);
    return;
}

void slist::display()
{
    node *temp=head;
    while(temp!=NULL)
    {
        cout<<"\n"<<temp->info<<"\n";
        temp=temp->next;
    }
}

void slist::breadthFirst(slist b[],inf c[],int i)
{
    int x;
    c[i+1].a=false;
    node *p = this->head;
    while(p!=0)
    {
        if(c[p->info].a)
        {
            c[p->info].b=i+1;
            c[p->info].a=false;
            b[p->info-1].breadthFirst(b,c,p->info-1);
        }
        else if(!((c[p->info].b==i+1)||(c[i+1].b==p->info)))
            b[i].deletenode(p->info);
            
        p=p->next;
    }
}

void slist::deletenode(int el)
{
    if(head==tail&&el==head->info)
    {
        delete	head;
        head=tail=0;
    }
    else if(head->info==el)
    {
        node *temp=head;
        head=head->next;
        delete temp;
    }
    else
    {
        node *pred,*temp;
        for	(pred=head,temp=head->next;temp!=0&&!(temp->info==el);pred=pred->next,temp=temp->next);
            if(temp!=0)
            {
                pred->next=temp->next;
                if(temp==tail)
                    tail=pred;
                    
                delete temp;
            }
    }
}

int main()
{
    int n,el,n1,start;
    slist *b;
    inf *c;
    cout<<"Enter the number of nodes you want to enter\n";
    cin>>n;
    c=new inf[n+1];
    b=new slist[n];
    for(int i=0;i<n;i++)
    {
        cout<<"Enter number of elements which are connected with "<<i+1<<" node.\n";
        cin>>n1;
        cout<<"\nEnter elements\n";
        for(int j=0;j<n1;j++)
        {
            cin>>el;
            b[i].addtotail(el);
        }
    }
    cout<<"\nEnter the value of starting point.\n";
    cin>>start;
    b[start-1].breadthFirst(b,c,start-1);
    cout<<"\n\n\n";
    for(int i=0;i<n;i++)
    {
        cout<<"\nAdjacent list for node "<<i+1;
        b[i].display();
    }
    return 0;
}
