#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int intIndex=0;

string lexemes[50];
string tokens[50];

int intValues[10];
string intVariableName[10];

int totalTokens = 0;
int totalLexemes = 0;

void initialize()
{
	string lexemes[10];
	string tokens[10];
	int totalTokens = 0;
	int totalLexemes = 0;
}

bool is_empty(char* filename)
{
    fstream ft;
    ft.open(filename, ios::in);
    ft.seekp(0,ios::end);
    bool answer= (ft.tellg()==0);
    ft.close();
    return answer;
}


bool startLine(string line1){
	int Finalstate=0;
	int k=0;
	while(line1[k]!='\n')
	{
		if(line1[k]=='m')
		{
			k=k+1;
			if(line1[k]=='a')
			{
				k=k+1;
				if(line1[k]=='i')
				{
					k=k+1;
					if(line1[k]=='n')
					{
						Finalstate=1;
					}					
				}
			}
		}
		k++;
		/*
		if(Finalstate==1)
		{
			if(line1[k]>='A' && line1[k]!=' ')
			{
				Finalstate=0;
			}
			
		}
		*/
	}
	
	if(Finalstate==1)
	{
	tokens[totalTokens] = "main";
	lexemes[totalLexemes] = "main";
	totalTokens++;
	totalLexemes++; 

		return true;
	}
	else
	{
		cout << "ERROR ON LINE 1" << endl;
		return false;
	}

}



bool lastLine(string line1, int currentLine){
	int Finalstate=0;
	int k=0;
	while(line1[k]!='\n')
	{
		if(line1[k]=='n')
		{
			k=k+1;
			if(line1[k]=='i')
			{
				k=k+1;
				if(line1[k]=='a')
				{
					k=k+1;
					if(line1[k]=='m')
					{
						Finalstate=1;
						break;
					}					
				}
			}
		}
		k++;
		/*
		if(Finalstate==1)
		{
			if(line1[k]>='A' && line1[k]!=' ')
			{
				Finalstate=0;
			}
			
		}
		*/
	}
	
	if(Finalstate==1)
	{
		tokens[totalTokens] = "niam";
		lexemes[totalLexemes] = "niam";
		totalTokens++;
		totalLexemes++; 
		return true;
	}
	else
	{
		return false;
	}

}


bool assigningCheck(string line,int currentLine)
{
	int k=0;
	while(line[k]!=';')
	{
		if(line[k]=='=')
		{
			return true;
		}
		k++;
	}
	return false;
}

void assigningIntValue(string line,int currentLine)
{
	string temp;
	string nameTemp;
	int nametempIndex=-1;
	int tempIndex=-1;
	int k=0;
	int AfterInt=-1;
	int assignOperator=0;
	while(line[k]!=';')
	{
		k++;		
		if(AfterInt==-1 && line[k]=='n')
			AfterInt++;
		else if(AfterInt==0 && line[k]=='t')
			AfterInt++;
		else if(assignOperator==0 && (line[k]>='A' && line[k]<='z') && AfterInt==1) // for getting the name of variable
		{
			nameTemp += line[k];
		}
		
		// for getting the value and then assigning to the variable
		if(line[k]=='=')
		{
			assignOperator=1;
			tokens[totalTokens] = "\\=";
			lexemes[totalLexemes] = "=";
			totalTokens++;
			totalLexemes++; 

		}
		else if(assignOperator==1 && (line[k]>='0' && line[k]<='9'))
		{
			tempIndex++;
			temp[tempIndex]=line[k];
		}
		else if(assignOperator==1 && (line[k]>='A' && line[k]<='z'))
		{
			cout << "ERROR SPOTTED ON LINE " << currentLine+1 << " WHILE ASSIGNING THE VALUE (VALUE HAS NOT BEING ASSIGNED PROPERLY)" << endl;
			break;
		}
		
		if(line[k+1] == ';' && tempIndex!=-1)
		{
			int value=0, i=0;
    		for (i = 0; i <= tempIndex; i++) {
 
		        // Since ASCII value of character from '0'
    	   	 	// to '9' are contiguous. So if we subtract
    		    // '0' from ASCII value of a digit, we get
      			// the integer value of the digit.
        		value = value * 10 + (temp[i] - '0');
    		}
    		intValues[intIndex] = value;
    		intVariableName[intIndex] = nameTemp;
    		intIndex++;
		}
		else if(line[k+1] == ';' && tempIndex==-1)
		{
			intValues[intIndex] = 0;
			intVariableName[intIndex] = nameTemp;
			intIndex++;
		}

	}
	
}

bool intCheck(string line, int currentLine){

	int Finalstate=0;
	int k=0;
	while(line[k]!=';')
	{
		if(line[k]=='i')
		{
			k++;
			if(line[k]=='n')
			{
				k++;
				if(line[k]=='t')
				{						 
					Finalstate=1;
					break;		
				}
			}
		}
		k++;
	}
	
	if(Finalstate==1)
	{
		tokens[totalTokens] = "int";
		lexemes[totalLexemes] = "int";
		totalTokens++;
		totalLexemes++;
		assigningIntValue(line, currentLine);
		return true;
	}
	else
	{
		return false;
	}
	

}


bool ifCheck(string line, int currentLine){

	int Finalstate=0;
	int k=0;
	while(line[k]!='\n')
	{
		if(line[k]=='i')
		{
			k++;
			if(line[k]=='f')
			{
				tokens[totalTokens] = "if";
				lexemes[totalLexemes] = "if";
				totalTokens++;
				totalLexemes++; 
				Finalstate=1;
										
			}
		}
		k++;
	}
	
	if(Finalstate==1)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool elseCheck(string line,int currentLine){
	int Finalstate=0;
	int k=0;
	while(line[k]!='\n')
	{
		if(line[k]=='e')
		{
			k++;
			if(line[k]=='l')
			{
				k++;
				if(line[k]=='s')
				{
					k++;
					if(line[k]=='e')
					{
						Finalstate=1;
				
					}
				}
						
			}
		}
		k++;
	}
	
	if(tokens[totalTokens-1] == "}" && Finalstate==1)
	{
		tokens[totalTokens] = "else";
		lexemes[totalLexemes] = "else";
		totalTokens++;
		totalLexemes++; 
		Finalstate=1;
		return true;
	}
	else
	{
		return false;
	}	
}

bool stopCheck(string line,int currentLine){
	int Finalstate=0;
	int k=0;
	while(line[k]!='\n')
	{
		if(line[k]=='s')
		{
			k++;
			if(line[k]=='t')
			{
				k++;
				if(line[k]=='o')
				{
					k++;
					if(line[k]=='p')
					{
						Finalstate=1;
				
					}
				}
						
			}
		}
		k++;
	}
	
	if(Finalstate==1)
	{
		tokens[totalTokens] = "stop";
		lexemes[totalLexemes] = "stop";
		totalTokens++;
		totalLexemes++; 
		Finalstate=1;
		return true;
	}
	else
	{
		return false;
	}	
}


bool resumeCheck(string line,int currentLine){
	int Finalstate=0;
	int k=0;
	while(line[k]!='\n')
	{
		if(line[k]=='r')
		{
			k++;
			if(line[k]=='e')
			{
				k++;
				if(line[k]=='s')
				{
					k++;
					if(line[k]=='u')
					{
						k++;
						if(line[k]=='m')
						{
							k++;
							if(line[k]=='e')
							{
								Finalstate=1;
				
							}		
						}
				
					}
				}
						
			}
		}
		k++;
	}
	
	if(Finalstate==1)
	{
		tokens[totalTokens] = "resume";
		lexemes[totalLexemes] = "resume";
		totalTokens++;
		totalLexemes++; 
		Finalstate=1;
		return true;
	}
	else
	{
		return false;
	}	
}


bool showString(string line,int currentLine){
	int k=0;
	int strCheck=0, varCheck=0;
	string temp="";
	
	while(line[k]!=';')
	{
		k++;
		if(line[k]=='"' && strCheck==0)
			strCheck=1;
		else if(strCheck==1 && line[k]=='"')
		{
			strCheck=0;
		}
		else if(line[k]=='{' && varCheck==0)
			varCheck=1;
		else if(line[k]=='}' && varCheck==1)
		{
			int variableFound=0;
			varCheck=0;
			for(int i=0; i<intIndex ; i++)
			{
				if(temp == intVariableName[i])
				{
					cout << intValues[i];
					variableFound=1;
					temp="";
				}
			}
			if(!variableFound)
			{
				return false;
			}
		}
		else if(strCheck==1 && varCheck==1)
		{
			temp += line[k];
			
		}
		else if(varCheck==0 && strCheck==1)
		{
			cout << line[k];
		}

	}
	return true;

}

bool showCheck(string line,int currentLine){
	int Finalstate=0;
	int k=0;
	while(line[k]!='\n')
	{
		if(line[k]=='s')
		{
			k++;
			if(line[k]=='h')
			{
				k++;
				if(line[k]=='o')
				{
					k++;
					if(line[k]=='w')
					{
						Finalstate=1;
				
					}
				}
			}
		}
		k++;
	}
	
	if(Finalstate==1)
	{
		tokens[totalTokens] = "show";
		lexemes[totalLexemes] = "show";
		totalTokens++;
		totalLexemes++; 
		bool check = showString(line,currentLine);
		if(!check)
		{
			return false;
		}
		return true;
	}
	else
	{
		return false;
	}	
}

bool OperationFinalizer(int Location, int value1, int value2, char operation)
{
				if(operation=='+')
				{
					intValues[Location]=value1+value2;
				}
				else if(operation=='-')
				{
					intValues[Location]=value1-value2;
				}
				else if(operation=='/')
				{
					intValues[Location]=value1/value2;
				}
				else if(operation=='*')
				{
					intValues[Location]=value1*value2;
				}
				string temp = "\\" ;
				temp += operation;
				tokens[totalTokens] = temp;
				lexemes[totalLexemes] = operation;
				totalTokens++;
				totalLexemes++; 

				
				
				return true;
}



bool OperationPerforming(string line,int currentline){
	int k=0;
	int varCheck=0;
	string temp1="";
	string temp2="";
	string temp3="";
	int value1=0;
	int value2=0;
	int valueLocation1=0;
	int valueLocation2=0;
	int valueLocation3=0;
	char operation;
	if(assigningCheck(line, currentline))
	{
		int length2=-1, length3=-1;
		int skip2=0, skip3=0;
		while(line[k]!=';')
		{
			if(line[k]=='=')
			{
				varCheck=1;
				tokens[totalTokens] = "\\=";
				lexemes[totalLexemes] = "=";
				totalTokens++;
				totalLexemes++; 

			}
			else if(line[k]=='+' || line[k]=='-' || line[k]=='*' || line[k]=='/')
			{
				operation = line[k];
				varCheck=2;
			}
			else if(varCheck==0 && (line[k]>='A' && line[k]<='z'))
			{
				temp1 += line[k];
			}
			else if(varCheck==1 && ((line[k]>='A' && line[k]<='z') || (line[k]>='0' && line[k]<='9')))
			{
				temp2 += line[k];
				length2++;
			}
			else if(varCheck==2 && ((line[k]>='A' && line[k]<='z') || (line[k]>='0' && line[k]<='9')))
			{
				temp3 += line[k];
				length3++;
			}
			k++;
		}
		
		
		int variableFound1=0,variableFound2=0,variableFound3=0;		
		if(temp2[0]>='0' && temp2[0]<='9')
		{	
			    for (int i = 0; i <= length2; i++) {
		        // Since ASCII value of character from '0'
    	   	 	// to '9' are contiguous. So if we subtract
    		    // '0' from ASCII value of a digit, we get
      			// the integer value of the digit.
        		value1 = value1 * 10 + (temp2[i] - '0');
    			}
    		skip2=1;	
    		variableFound2=1;
		}
		
		if(temp3[0]>='0' && temp3[0]<='9')
		{	
			    for (int i = 0; i <= length3; i++) {
		        // Since ASCII value of character from '0'
    	   	 	// to '9' are contiguous. So if we subtract
    		    // '0' from ASCII value of a digit, we get
      			// the integer value of the digit.
        		value2 = value2 * 10 + (temp3[i] - '0');
    			}
     		skip3=1;
    		variableFound3=1;
		}

		
		
		
		varCheck=0;
		for(int i=0; i<intIndex ; i++)
		{
		
			if(temp1 == intVariableName[i])
			{
				valueLocation1=i;
				variableFound1=1;
			}
			else if(temp2 == intVariableName[i] && skip2==0)
			{
				valueLocation2=i;
				variableFound2=1;

			}
			else if(temp3 == intVariableName[i] && skip3==0)
			{
				valueLocation3=i;
				variableFound3=1;
			}
				
			if(variableFound1==1 && variableFound2==1 && variableFound3==1)
			{
				varCheck=1;
				break;
			}
		}
		
		if(varCheck==0)
		{
			return false;
		}
		else
		{
			if(skip2==0 && skip3==0)
			{
				OperationFinalizer(valueLocation1, intValues[valueLocation2], intValues[valueLocation3], operation);
			}
			else if(skip2==1 && skip3==0)
			{
				OperationFinalizer(valueLocation1, value1, intValues[valueLocation3], operation);
			}
			else if(skip2==0 && skip3==1)
			{
				OperationFinalizer(valueLocation1, intValues[valueLocation2], value2, operation);
			}
			else if(skip2==1 && skip3==1)
			{
				OperationFinalizer(valueLocation1, value1, value2, operation);
			}
			else
			{
				return false;
			}
			
			return true;
		}
		
	}
	else
	{
		return false;
	}		
}

bool askiSave(string line,int currentLine){
	int k=0;
	int varCheck=0;
	string temp="";
	
	while(line[k]!=';')
	{
		k++;
		if(line[k]=='"' && varCheck==0)
		{
			varCheck=1;
		}
		else if(varCheck==1 && line[k]=='"')
		{
			int variableFound=0;
			varCheck=0;
			for(int i=0; i<intIndex ; i++)
			{
				if(temp == intVariableName[i])
				{
					int value=0;
					variableFound=1;
					cin >> value;
					intValues[i]=value;
				}
			}
			
			if(!variableFound)
			{
				return false;
			}
		}
		else if(varCheck==1)
		{
			temp += line[k];
			
		}

	}
	cout << endl;

}

bool askiCheck(string line,int currentLine){
	int Finalstate=0;
	int k=0;
	while(line[k]!='\n')
	{
		if(line[k]=='a')
		{
			k++;
			if(line[k]=='s')
			{
				k++;
				if(line[k]=='k')
				{
					k++;
					if(line[k]=='i')
					{
						Finalstate=1;
				
					}
				}
			}
		}
		k++;
	}
	
	if(Finalstate==1)
	{
		tokens[totalTokens] = "aski";
		lexemes[totalLexemes] = "aski";
		totalTokens++;
		totalLexemes++;
		bool check = askiSave(line,currentLine);
		if(!check)
		{
			return false;
		}
		return true;
	}
	else
	{
		return false;
	}	
}



bool middleCode(string line, int currentLine){
	
	bool checker=false;
	int k=0;
	while(line[k]!='\n')
	{
		if(line[k]=='i')
		{
			checker = intCheck(line, currentLine);
			if(!checker)
			{
				checker = ifCheck(line, currentLine);
				if(!checker)
				{
					checker = OperationPerforming(line, currentLine);
				}
			}
			break;
		}
		else if(line[k]=='e')
		{
			checker = elseCheck(line, currentLine);
			if(!checker)
			{
				checker = OperationPerforming(line, currentLine);
			}
			break;
		}
		else if(line[k]=='a')
		{
			checker = askiCheck(line, currentLine);
			if(!checker)
			{
				checker = OperationPerforming(line, currentLine);
			}
			break;

		}

		else if(line[k]=='s')
		{
			checker = showCheck(line, currentLine);
			if(!checker)
			{
				checker = stopCheck(line, currentLine);
				if(!checker)
				{
					checker = OperationPerforming(line, currentLine);
				}
			}
			break;
		}
		else if(line[k]==' ')
		{
			k++;			
			continue;
		}
		else
		{
			checker = OperationPerforming(line, currentLine);
			break;
		}
	}
	
	if(!checker)
	{
		cout << "ERROR ON LINE " << currentLine+1  << endl;
		return false;
	}
	return true;
}



bool Parse(string* code, int totalLines){
	
	int currentLine=0;
	for(currentLine=0; currentLine<totalLines; currentLine++)
	{
		if(currentLine==0)
		{
			bool LineChecked= startLine(code[currentLine]);
			if(!LineChecked)
			{
				return false;
			}
		}
		
		
		if(currentLine!=0 && code[currentLine][0]!='n')
		{
			bool LineChecked= middleCode(code[currentLine], currentLine);
			if(!LineChecked)
			{
				return false;
			}
		}	
		
		
		if(code[currentLine][0]=='n')
		{
			bool LineChecked= lastLine(code[currentLine], currentLine);
			if(!LineChecked)
			{
				cout << "ERROR ON LINE " << currentLine+1  << endl;
				return false;
			}
		}
	}

	return true;
	
}



void CreateTokensFile()
{
	int i=0;
    fstream ft1;
    ft1.open("CorrectCodeTokes.txt", ios::out);
    ft1 << "Lexemes" << setw(40) << right << "Tokens" << endl;
    ft1 << "--------------------------------------------------------" << endl;
    for(i=0;i<=totalTokens;i++)
    {
		    ft1 << lexemes[i] << setw(40) << right << tokens[i] << endl;    	
	}
	ft1 << "--------------------------------------------------------" << endl;
    ft1 << "Total tokens = " << totalTokens << endl;
    	
    ft1.close();
}





int main(){
	int i=0;
    string read;
    string line[100];
    ifstream ft("CorrectCode.txt");
    if(!is_empty("CorrectCode.txt"))
    {
		while( getline(ft,read) )
        {
            line[i] = read;
            i++;
        }
    }
    else
    {
        cout << "Empty File";
        return 0;
    }
    ft.close();

    bool codeChecked = Parse(line, i);
    
    if(codeChecked)
	{
		CreateTokensFile();
	}

    return 0;
}
