#include <iostream>
#include <string>
#include <fstream>

using namespace std;

fstream archivo;fstream archivo1;ofstream write;ofstream write1;

string toBinary(int num){

    string bin, binario="0";

    while(num>0){
        if(num%2==0){
            bin=bin+"0";
        }else{
            bin=bin+"1";
        }
        num=num/2;
    }

    for(int i=6;i>=0;i--){
       binario+=bin[i];
    }
    return binario;
}

string toString(string binario){

    int len=binario.size();
    string num, cadena;
    int aux[]={1,2,4,8,16,32,64,128,256};
    int i=0;
    int digito;
    int res, cont=0;
    char letra;

    while(i<len){

        for(int j=0;j<=7;j++){
            num[j]=binario[i];
            i++;
        }
        for(int j=7;j>=0;j--){
            digito=num[j];
            if(digito=='1'){
                res=res+aux[cont];
            }
            cont++;
        }
        letra=res;
        cont=0,res=0;;
        cadena+=letra;

    }
    return cadena;
}

string decodificacion1(string binario, int semilla){

    string copia=binario;
    int len=binario.size();
    int a=0, j=0,k=0;
    int seed=semilla;
    int cero=0, uno=0;

    for(int i=0;i<semilla;i++){
        if(binario[i]=='0'){
            binario[i]='1';
        }else{
            binario[i]='0';
        }
    }

    while(semilla<=len){

        //saber la cantidad de 1 y 0 del grupo anterior
        for(int i=a; i<(semilla+semilla)/2;i++){
            if(binario[i]=='0'){
                cero+=1;
            }else{
                uno+=1;
            }
        }

        if(uno==cero){
            for(int i=semilla;i<(semilla+4);i++){
                if(binario[i]=='0'){
                    binario[i]='1';
                }else{
                    binario[i]='0';
                }
            }
        }

        if (cero>uno){

            j=semilla+1;
            while  (j<=semilla+4 && j<=len){
                if(j%2==0){
                    if(binario[j-1]=='0'){
                        binario[j-1]='1';
                    }else{
                        binario[j-1]='0';
                    }
                }
            j=j+1;
            }
        }

        if(uno>cero){

            k=semilla+2;
            while(k<semilla+4){
                if(copia[k]=='0'){
                    binario[k]='1';
                }else{
                    binario[k]='0';
                }
            k=k+2;
            }
        }

        a=a+seed;
        semilla=semilla+seed;
        cero=0;uno=0;
    }
    return binario;
}

string decodificacion2(string binario, int semilla){

    string copia=binario;
    int len=binario.size();
    int seed=semilla;
    int a=0;

    while(semilla<=len){

        for(int i=a;i<semilla;i++){
            if(i==semilla-1){
                binario[semilla-1]=copia[a];
            }else{
                binario[i]=copia[i+1];
            }
        }

        a=semilla;
        semilla=seed+semilla;

    }
    return binario;
}

string metodo1(string binario, int semilla){

    string copia=binario;
    int len=binario.size();
    int a=0, j=0,k=0;
    int seed=semilla;
    int cero=0, uno=0;

    for(int i=0;i<semilla;i++){
        if(binario[i]=='0'){
            binario[i]='1';
        }else{
            binario[i]='0';
        }
    }

    while(semilla<=len){

        //saber la cantidad de 1 y 0 del grupo anterior
        for(int i=a; i<(semilla+semilla)/2;i++){
            if(copia[i]=='0'){
                cero+=1;
            }else if(copia[i]=='1'){
                uno+=1;
            }
        }

        if(uno==cero){
            for(int i=semilla;i<(semilla+4);i++){
                if(copia[i]=='0'){
                    binario[i]='1';
                }else{
                    binario[i]='0';
                }
            }
        }

        if(uno>cero){

            k=semilla+1;
            while(k<semilla+4){
                if(copia[k]=='0'){
                    binario[k]='1';
                }else{
                    binario[k]='0';
                }
            k=k+2;
            }
        }

        if (cero>uno){

            j=semilla+1;
            while  (j<=semilla+4 and j<=len){
                if(j%2==0){
                    if (copia[j-1]=='0'){
                        binario[j-1]='1';
                    }else{
                        binario[j-1]='0';
                    }
                }
            j=j+1;
            }
        }

        a=a+seed;
        semilla=semilla+seed;
        cero=0;uno=0;
    }
    return binario;
}

string metodo2(string binario,int semilla){

    string copia=binario;
    int len=binario.size();
    int seed=semilla;
    int a=0;

    while(semilla<=len){

        for(int i=a;i<semilla;i++){
            if(i==a){
                binario[i]=copia[semilla-1];
            }else{
                binario[i]=copia[i-1];
            }
        }

        a=semilla;
        semilla=seed+semilla;

    }
    return binario;
}

int main(){

    archivo.open("file.txt");
    archivo1.open("file.txt");
    int len=0;

    for(int i=0;!archivo.eof();i++){
        archivo.get();
        len=i;
    }

    archivo.close();

    int acii;
    int semilla;
    int metodo;
    string binario="";

    for(int i=0;i<len;i++){
        char letra=archivo1.get();
        acii=letra;
        binario+=toBinary(acii);
    }

    archivo1.close();
    cout<<"El binario a codificar es: "<<binario<<endl;
    cout<<"\n";
    cout<<"Ingrese el numero semilla (par): ";cin>>semilla;

    if(semilla%2!=0){
        cout<<"Error"<<endl;
        exit(1);
    }

    cout<<"\n";
    cout<<"Ingrese el metodo de codificacion y decodificacion 1-2: ";cin>>metodo;

    if(semilla%2!=0){
        cout<<"Error"<<endl;
        exit(1);
    }

    write.open("codificaco.txt");
    write1.open("decodificado.txt");

    if(metodo==1){
        string cod1=metodo1(binario, semilla);
        cout<<"El binario codificado por el metodo 1 es: "<<metodo1(binario,semilla)<<endl;
        cout<<"El binario decodificado por el metodo 1 es: "<<decodificacion1(cod1, semilla)<<endl;
        cout<<"La palabra decodificada es: "<<toString(binario)<<endl;
        write<<metodo1(binario,semilla);
        write1<<decodificacion1(cod1,semilla)<<" , "<<toString(binario);
        write.close(); write1.close();

    }else if(metodo==2){
        string cod2=metodo2(binario,semilla);
        cout<<"El binario codificado por el metodo 2 es: "<<metodo2(binario,semilla)<<endl;
        cout<<"El binario decodificado por el metodo 2 es: "<<decodificacion2(cod2,semilla)<<endl;
        cout<<"La palabra decodificada es: "<<toString(binario)<<endl;
        write<<metodo2(binario,semilla);
        write1<<decodificacion2(cod2,semilla)<<" , "<<toString(binario);
        write.close(); write1.close();

    }else{
        write.close(); write1.close();
        cout<<"Error"<<endl;
        exit(1);
    }

    return 0;
}
