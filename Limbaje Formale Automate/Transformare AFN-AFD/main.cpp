#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

ifstream f("date.in");

string FromCharToString(char caracter)
{
    string s(1, caracter);
    return s;
}

string FromIntToString(int caracter)
{
    string s;
    ostringstream convert;
    convert<<caracter;
    s=convert.str();
    return s;
}

int comparare_stringuri(string a,string b)
{
    if(a.compare(b)==0)
        return 1;
    return 0;
}

string get_stare1(string a)
{
    int i=0;
    string b;

    while(a[i]!='-')
        i++;

    b.resize(i);

    for(int j=0;j<=i-1;j++)
        b[j]=a[j];

    return b;
}

char get_simbol(string a)
{
    int i=0;
    while(a[i]!='-')
        i++;
    return a[i+1];
}

string get_stare2(string a)
{
    int i=a.length(),nr=0;
    string b;

    while(a[i]!='-')
    {
        i--;
        nr++;
    }

    b.resize(nr-1);
    nr=0;

    for(int j=i+1; j<=a.length()-1; j++)
    {
        b[nr]=a[j];
        nr++;
    }

    return b;
}

int cautare_simbol(char x,string s)
{
    int ok=0;
    for(int i=0;i<=s.length()-1;i++)
        if(s[i]==x)
        ok=1;

   return ok;
}

string ordonare_s1(string a)
{
    string b=get_stare1(a);
    char aux;

    for(int i=0;i<=b.length()-3;i+=2)
    {
        for(int j=i+2;j<=b.length()-1;j+=2)
        {
            if(a[i]>a[j])
            {
                aux=a[i];
                a[i]=a[j];
                a[j]=aux;
            }

        }
    }
    return a;
}

string ordonare_s2(string a)
{
    string b=get_stare2(a);
    char aux;

    for(int i=a.length()-b.length(); i<=a.length()-3; i+=2)
    {
        for(int j=i+2; j<=a.length()-1; j+=2)
        {
            if(a[i]>a[j])
            {
                aux=a[i];
                a[i]=a[j];
                a[j]=aux;
            }

        }
    }
    return a;
}

int main()
{
    int stari_finale[10],numar_stari,numar_stari_finale,stare1,stare2,numar_simboluri,nr=-1,nr_aux;
    string a[10][10];
    char alfabet[10],aux,x;

    vector <string> stari_noi;
    vector <string> stari_vechi;
    map <string,string> stari;

    f>>numar_stari;
    f>>numar_stari_finale;

    for(int i=0; i<=numar_stari_finale-1; i++)
        f>>stari_finale[i];

    f>>numar_simboluri;
    for(int i=0; i<=numar_simboluri-1; i++)
        f>>alfabet[i];

    string c;

    while(!f.eof())
    {
        nr++;
        f>>stare1;
        f>>aux;
        f>>stare2;
        a[stare1][stare2]+=aux;

        c=FromIntToString(stare1)+ "-" +FromCharToString(aux)+ "-" +FromIntToString(stare2);
        stari_vechi.push_back(c);

    }

    stari_vechi.pop_back();

    string c1;
    int lungime;

    if(a[numar_stari-1][numar_stari-1].length()>1)
    {
        c1=a[numar_stari-1][numar_stari-1];
        lungime=c1.length();
        c1[lungime-1]=0;
        a[numar_stari-1][numar_stari-1]=c1;
    }

    for(int i=0; i<=numar_stari-1; i++)
        for(int j=0; j<=numar_stari-1; j++)
        {
            if(a[i][j].empty())
                a[i][j]='0';
        }


    for(int i=0; i<=numar_stari-1; i++)
    {
        for(int j=0; j<=numar_stari-1; j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;


    nr_aux=nr;
    string s1_stare1,s2_stare1,s1_stare2,s2_stare2,auxiliar,s1_aux,s2_aux,element_matrice,c_a,c_b;
    char s1,s2;
    int i1,i2,ok,verific,var;

    for(i1=0; i1<=nr_aux-2; i1++)
    {
        ok=0;
        stari.clear();
        s1_stare1=get_stare1(stari_vechi[i1]);
        s1_aux=get_simbol(stari_vechi[i1]);
        auxiliar=get_stare2(stari_vechi[i1]);

        for(i2=i1+1; i2<=nr_aux-1; i2++)
        {
            s2_stare1=get_stare1(stari_vechi[i2]);
            s2_aux=get_simbol(stari_vechi[i2]);


            if(s1_stare1==s2_stare1 && s1_aux==s2_aux)
            {
                ok=1;
                auxiliar+=",";
                auxiliar+=get_stare2(stari_vechi[i2]);
            }

            verific =1;
            if(ok)
            {
                for(int i3=0; i3<=stari_vechi.size()-1; i3++)
                {
                    if(comparare_stringuri(get_stare1(stari_vechi[i3]),auxiliar))
                        verific=0;
                }

                if(verific)
                {

                    c_a=auxiliar+"-"+"a"+"-";
                    c_b=auxiliar+"-"+"b"+"-";

                    for(int i4=0; i4<=numar_stari-1; i4++)
                    {
                        if(auxiliar.find_first_of(FromIntToString(i4)) != string::npos)
                        {
                            var=i4;

                            for(int i5=0; i5<=numar_stari-1; i5++)
                            {
                                if(a[var][i5]!="0")
                                {
                                    element_matrice=a[var][i5];

                                    for(int i6=0; i6<=element_matrice.length()-1; i6++)
                                    {

                                        stari.insert(pair<string,string>(FromCharToString(element_matrice[i6]),FromIntToString(i5)));
                                        if(element_matrice[i6]=='a' && get_stare2(c_a).find(stari["a"]) == string::npos)
                                            c_a+=stari["a"]+",";
                                        if(element_matrice[i6]=='b' && get_stare2(c_b).find(stari["b"]) == string::npos)
                                            c_b+=stari["b"]+",";
                                        stari.clear();

                                    }

//
                                }


                            }

                        }

                    }
                    nr_aux+=2;
                    c_a.resize(c_a.size()-1);
                    c_b.resize(c_b.size()-1);
                    stari_vechi.push_back(c_a);
                    stari_vechi.push_back(c_b);

                }
            }

        }
    }


//    for(int i=0; i<=stari_vechi.size()-1; i++)
//        cout<<stari_vechi[i]<<endl;
//    cout<<endl;

    int index=nr_aux;

    for(i1=nr; i1<=stari_vechi.size()-1; i1++)
    {
        ok=1;
        s1_stare2=get_stare2(stari_vechi[i1]);
        s1_aux=get_simbol(stari_vechi[i1]);

        for(i2=0; i2<i1; i2++)
        {
            s2_stare1=get_stare1(stari_vechi[i2]);
            s2_aux=get_simbol(stari_vechi[i2]);
            if(comparare_stringuri(s1_stare2,s2_stare1))
            {
                if(s1_aux==s2_aux)
                    ok=0;
                else
                    ok=1;
            }

        }

        if(ok)
        {
            if (get_stare1(stari_vechi[i1]) != s1_stare2)
            {
                if(s1_aux=="a")
                    c_a=s1_stare2+"-a-";

                if(s1_aux=="b")
                    c_b=s1_stare2+"-b-";

            }

            else
            {
                if (s1_aux == "a")
                {
                    c_b = s1_stare2 + "-b-";
                    s1_aux = "b";
                }
                else
                {
                    c_a = s1_stare2 + "-a-";
                    s1_aux = "a";
                }
            }
            for(int i3=0; i3<=nr-1; i3++)
            {
                s1=get_stare1(stari_vechi[i3])[0];
                s2=get_stare2(stari_vechi[i3])[0];

                if(cautare_simbol(s1,s1_stare2) && s1_aux==FromCharToString(get_simbol(stari_vechi[i3])))
                {

                    if(s1_aux=="a")
                    {
                        if (get_stare2(c_a).find(FromCharToString(s2)) == string::npos)
                            c_a = c_a + s2 + ",";
                    }

                    if(s1_aux=="b")
                    {
                        if (get_stare2(c_b).find(FromCharToString(s2)) == string::npos)
                            c_b = c_b + s2 + ",";
                    }
                }


            }
            if(s1_aux=="a")
            {
                c_a.resize(c_a.size()-1);
                if (find(stari_vechi.begin(), stari_vechi.end(), c_a) == stari_vechi.end())
                    stari_vechi.push_back(c_a);
            }
            if(s1_aux=="b")
            {
                c_b.resize(c_b.size()-1);
                if (find(stari_vechi.begin(), stari_vechi.end(), c_b) == stari_vechi.end())
                    stari_vechi.push_back(c_b);
            }
            nr_aux++;

        }

    }

    for(int i=nr; i<=stari_vechi.size()-1; i++)
    {
        stari_vechi[i]=ordonare_s1(stari_vechi[i]);
        stari_vechi[i]=ordonare_s2(stari_vechi[i]);

    }


    for(int i1=0; i1<=nr-2; i1++)
    {
        s1_stare1=get_stare1(stari_vechi[i1]);
        s1_aux=get_simbol(stari_vechi[i1]);
        s1_stare2=get_stare2(stari_vechi[i1]);
        auxiliar.clear();

        for(int i2=i1+1; i2<=nr-1; i2++)
        {
            s2_stare1=get_stare1(stari_vechi[i2]);
            s2_aux=get_simbol(stari_vechi[i2]);
            s2_stare2=get_stare2(stari_vechi[i2]);

            if(s1_stare1==s2_stare1 && s1_aux==s2_aux)
            {
                auxiliar=s1_stare1+"-"+s1_aux+"-"+s1_stare2+","+s2_stare2;
                stari_vechi[i1]=auxiliar;
                stari_vechi.erase(stari_vechi.begin()+i2);
                nr--;
            }


        }

    }

                                                                                                                                                                                                //stari_vechi.erase(stari_vechi.begin()+2); stari_vechi.erase(stari_vechi.begin()+2); stari_vechi.erase(stari_vechi.begin()+2); stari_vechi.erase(stari_vechi.begin()+2); stari_vechi.erase(stari_vechi.begin()+2);
                                                                                                                                                                                                //stari_vechi.erase(stari_vechi.begin()+4); stari_vechi.erase(stari_vechi.begin()+4);
    int i=0,j,l=0;

    while(i<=stari_vechi.size()-2)
    {
        s1_stare2=get_stare2(stari_vechi[i]);
        for(int j=i+1; j<=stari_vechi.size()-1; j++)
        {
            s2_stare1=get_stare1(stari_vechi[j]);
            if(s1_stare2==s2_stare1)
            {
                stari_noi.push_back(stari_vechi[i]);
                l++;
                break;
            }

        }
        i++;
    }

}
