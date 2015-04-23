#include<iostream>
#include<sstream>
#include<string>
#include<conio.h>
#include<vector>
#include<stdio.h>
using namespace std;

class attribute
{
public:
	string name;
	string value;
	attribute()
	{
		name=value="";
	}
};

class xmlnode
{
public:
	string nodeName;
	xmlnode * parent;
	vector<attribute> attrib;
	string data;
	vector<xmlnode *> child;
	xmlnode()
	{
		nodeName=data="";
		parent=NULL;
	}
};

xmlnode parse(string in)
	{
		int flag;//flag==0 
		int i=0,j=0;
		int count=0;
		xmlnode temp;
		while(i!=180)
		{
		if(in[i]=='>')
		{
			flag=0;
			break;
			i++;
		}
		if(in[i]==' ')
		{
			i++;
		}
		if(in[i]=='<')
				{
					flag=1;
					i++;
					count++;
				}
				if(flag==1)
				{
					while(in[i]!=' '&&in[i]!='>')
					{
						temp.nodeName.push_back(in[i]);
						i++;
					}
					flag=2;
					if(in[i]=='>')
					break;
					i++;
				}
				string dum1,dum2;
				if(flag==2)
				{
					
					while(in[i]!='=')
					{
						dum1.push_back(in[i]);
						i++;
					}
					flag=3;
					i++;
				}
				
				if(flag==3)
				{
					if(in[i]='"')
					{
						i++;
						string dum2;
						while(in[i]!='"')
						{
							dum2.push_back(in[i]);
							i++;
						}
						attribute temp2;
						temp2.name=dum1;
						temp2.value=dum2;
						temp.attrib.push_back(temp2);
						flag=2;
					}
				}
				i++;
			}
			return temp;
			
	}
vector<string> pathsplitter(string path)
{
	vector<string> r;
	string temp;
	for(int i=1;i<path.length();i++)
	{
		
		if(path[i]=='/')
		{
			r.push_back(temp);
			//cout<<temp<<endl;
			temp="";
			continue;
		}
		temp+=path[i];
	}
	return r;
}
xmlnode * stringparse(xmlnode * r, string content, string tag, string name)
{
	xmlnode * temp=new  xmlnode;
	temp->parent=r;
	temp->attrib=parse(tag).attrib;
	temp->nodeName=name;
	istringstream contentss(content);
	string w;
	int count=0;
	while(contentss>>w)
	{
		
		if(w[0]=='<')
		{

			string namenew=w;
			string tagnew=w;
			string c;
			if(w[w.length()-1]!='>')
			{
			while(tagnew[tagnew.length()-1]!='>')
			{
			contentss>>c;
			if(tagnew[tagnew.length()-1]!='>')
			{
			tagnew.append(" ");
			}
			tagnew.append(c);
			
			}
			}
			namenew=namenew.substr(1,namenew.length());
			if(namenew[namenew.length()-1]=='>')
			{
				namenew=namenew.substr(0,namenew.length()-1);
			}
			string ends="</"+namenew+">";
		
			string contentnew="";
			string temps;
			while(contentss>>temps)
			{
				if(temps[0]=='<')
				{
				//cout<<temps<<"  "<<ends<<(temps==ends)<<endl;
				}
				if(temps!=ends)
				{
				contentnew.append(temps);
				contentnew+=" ";
				}
				else break;
			
			}
			//cout<<endl<<contentnew<<endl;
			temp->child.push_back(stringparse(temp,contentnew,tagnew,namenew)); 
		}
		
		else
		{
			temp->data.append(w);
			temp->data+=" ";
		}
	}
	return temp;
}
class xmltree
{
	
	public:
	xmlnode * root;
	xmltree()
	{
		root=NULL;
	}
	void createnode(xmlnode * r)
	{
		xmlnode * temp =new xmlnode;
		temp->parent=r;
		

	};


	bool parse()
	{
		freopen( "movies.xml", "r", stdin );

		string s;
		xmlnode * current = root;
		cin>>s;
		string tag=s;
		if(s[0]!='<')
		{
			cout<<"not well formed xml u shithead";
			return 0;
		}
			
		else
		{
			string c;
			while(tag[tag.length()-1]!='>')
			{
			cin>>c;
			if(tag[tag.length()-1]!='>')
			{
			tag.append(" ");
			}
			tag.append(c);
			
			}
		}
		
		s=s.substr(1,s.length());
		string ends;
		ends="</"+s+">";
		string content;
		string temp;
		while(1)
		{
			cin>>temp;
			if(temp!=ends)
			{
				content.append(temp);
				content+=" ";
			}
			else break;
			
		}
		root=stringparse(root,content,tag,s);
		return 1;
	} 

	vector<xmlnode *> gettopath(xmlnode * root,string path,int depth=0)
	{
		xmlnode * current=root;
		vector<string> paths=pathsplitter(path);
		vector<xmlnode *> r;
		if(depth==paths.size())
		{
			for(int i=0;i<root->child.size();i++)
			{
				//cout<<root->child[i]->nodeName<<endl;
				r.push_back(root->child[i]);
			}
		}
		else
		{
			for(int i=0;i<root->child.size();i++)
			{
				if(root->nodeName==paths[depth])
				{
					for(int i=0;i<root->child.size();i++)
					{
						r.insert(r.end(),gettopath(root->child[i],path,depth+1).begin(),gettopath(root->child[i],path,depth+1).end());
					}
				}
			}
		}
		return r;
	}
};


void listallnodes(xmlnode * root)
{
	if(root==NULL)
	{
		return;
	}
	else
	{
		cout<<root->nodeName<<endl;
		for(int i=0;i<root->child.size();i++)
		{
			listallnodes(root->child[i]);
		}
	}
}


void search(xmltree r,string path, attribute a)
{
	if(r.root==NULL)
	{
		return;
	}
	else
	{
		vector<xmlnode *> list=r.gettopath(r.root,path);
		for(int i=0;i<list.size();i++)
		{
			cout<<list[i]->nodeName<<endl;
		}
	}
}

int main()
{
	xmltree x1;
	x1.parse();
	attribute a;
	//search(x1,"/collection/movies/",a);
	//pathsplitter("/collection/movies/");
	vector<xmlnode *> r=x1.gettopath(x1.root,"/collection/movies");
	for(int i=0;i<r.size();i++)
	{
		cout<<r[i]->nodeName<<endl;
	}
	getch();
}
