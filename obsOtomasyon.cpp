#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student
{
private:
    string isimOgrenci;
    string soyAdOgrenci;
    int numOkul;
    float notVize,notFinal,notOrt;
public:
    void setOgrenci(string ad,string soyad,int num,float vize,float final,float ort){
        isimOgrenci = ad;
        soyAdOgrenci = soyad;
        numOkul = num;
        notVize = vize;
        notFinal = final;
        notOrt = ort;
    }
    bool getOgrenci(int sNumber){
        if (sNumber==numOkul)
        {
            return true;
        }
        else{
            return false;
        } 
    }
    void getOgrenciBilgi(){
        cout<<"Adı: "<<isimOgrenci<<endl<<"Soyadı: "<<soyAdOgrenci<<endl<<"Okul Numarası: "<<numOkul<<endl;
        cout<<"Vize: "<<notVize<<endl<<"Final: "<<notFinal<<endl<<"Ortalama: "<<notOrt<<endl;
    }
    void kaydetOgrenciBilgi(){
        ofstream myData("DataBase.txt",ios::app);
        myData<<"Adı: "<<isimOgrenci<<endl<<"Soyadı: "<<soyAdOgrenci<<endl<<"Okul Numarası: "<<numOkul<<endl<<"Vize: "<<notVize<<endl<<"Final: "<<notFinal<<endl<<"Ortalama: "<<notOrt<<endl<<endl;
        myData.close();
    }
    Student* next;
};

Student* head = NULL;
Student* tail = NULL;

void ekleOgrenci(string ad,string soyad,int okulNum,float vize,float final);
void bulOgrenci(int sNum);
void silOgrenci(int sNum);
void duzenleOgrenci(int sNum,string ad,string soyad,int okulNum,float vize,float final);
void kaydetOgrenciler();
int main(int argc, char const *argv[])
{
    string name,surname;
    int secim,okulnum,newOkulNum;
    float vize,final;
    bool _bool = true;
    while (_bool)
    {
        cout<<"\n1.\tÖğrenci Ekle\n2.\tÖğrenci Bul\n3.\tÖğrenci Düzenle\n4.\tÖğrenci Sil\n5.\tKaydet\n6.\tÇık\nSeçiminiz: ";
        cin>>secim;
        switch (secim)
        {
        case 1:
            cout<<"Öğrencinin Adı: ";
            getline(cin>>ws,name);
            cout<<"Öğrencinin Soyadı: ";
            getline(cin>>ws,surname);
            cout<<"Öğrencinin Okul Numarası: ";
            cin>>okulnum;
            cout<<"Vize Notu: ";
            cin>>vize;
            cout<<"Final Notu: ";
            cin>>final;
            ekleOgrenci(name,surname,okulnum,vize,final);
            break;
        case 2:
            cout<<"Öğrencinin Okul Numarasını Giriniz: ";
            cin>>okulnum;
            bulOgrenci(okulnum);
            break;
        case 3:
            cout<<"Düzenlenecek Öğrencinin Okul Numarası: ";
            cin>>okulnum;
            cout<<"Öğrencinin Adı: ";
            getline(cin>>ws,name);
            cout<<"Öğrencinin Soyadı: ";
            getline(cin>>ws,surname);
            cout<<"Öğrencinin Okul Numarası: ";
            cin>>newOkulNum;
            cout<<"Vize Notu: ";
            cin>>vize;
            cout<<"Final Notu: ";
            cin>>final;
            duzenleOgrenci(okulnum,name,surname,newOkulNum,vize,final);
            break;    
        case 4:
            cout<<"Sistemden Silinecek Öğrencinin Numarası: ";
            cin>>okulnum;
            silOgrenci(okulnum);
            break;
        case 5:
            kaydetOgrenciler();
            break;        
        default:
            cout<<"\nHatalı Giriş Yaptınız!\n";
            break;
        }
    }
    return 0;
}

void ekleOgrenci(string ad,string soyad,int okulNum,float vize,float final){
    float ort = vize*0.4+final*0.6;
    if (head==NULL)
    {
        head = new Student();
        
        head->setOgrenci(ad,soyad,okulNum,vize,final,ort);
        head->next = NULL;
        tail = head;
        cout<<"\nÖğrenci Sisteme Eklendi!\n";
    }
    else{
        tail->next = new Student();
        tail = tail->next;
        tail->setOgrenci(ad,soyad,okulNum,vize,final,ort);
        tail->next = NULL;
        cout<<"\nÖğrenci Sisteme Eklendi!\n";
    }
}

void bulOgrenci(int sNum){
    Student* iter = head;
    if (head==NULL)
    {
        cout<<"\nHenüz Eklenen Öğrenci Yok!\n";
        return ;
    }
    else{
        while (iter!=NULL)
        {
            if (iter->getOgrenci(sNum))
            {
                iter->getOgrenciBilgi();
                break;
            }
            iter = iter->next;
        }
        
    }
    
}

void silOgrenci(int sNum){
    if (head==NULL)
    {
        cout<<"\nVeri Boş!\n";
    }
    else if (head->next==NULL&&head->getOgrenci(sNum)==true)
    {
        Student* temp = head;
        head = NULL;
        delete temp;
        cout<<"\nÖğrenci Sistemden Silindi!\n";
    }
    else if(head->getOgrenci(sNum)){
        Student* temp = head;
        head = head->next;
        delete temp;
        cout<<"\nÖğrenci Sistemden Silindi!\n";
    }
    else if(tail->getOgrenci(sNum)){
        Student* iter = head;
        while (iter->next!=tail)
        {
            iter = iter->next;
        }
        Student* temp = tail;
        tail = iter;
        tail->next = NULL;
        delete temp;
        cout<<"\nÖğrenci Sistemden Silindi!\n";
    }
    else{
        Student* iter = head;
        while (iter->next!=NULL)
        {
            if (iter->next->getOgrenci(sNum))
            {
                Student* temp = iter->next;
                iter->next = iter->next->next;
                delete temp;
                cout<<"\nÖğrenci Sistemden Silindi!\n";
            }    
        }    
    }
}

void duzenleOgrenci(int sNum,string ad,string soyad,int okulNum,float vize,float final){
    float ort = vize*0.4+final*0.6;
    if (head==NULL)
    {
        cout<<"\nHenüz Sisteme Öğrenci Eklenmemiş!\n";
    }
    else{
        Student* iter = head;
        while (iter!=NULL)
        {
            if (iter->getOgrenci(sNum))
            {
                iter->setOgrenci(ad,soyad,okulNum,vize,final,ort);
            }
            cout<<"\nÖğrenci Bilgileri Güncellendi!\n";
            break;
        }
        iter = iter->next;
    }   
}
void kaydetOgrenciler(){
    Student* iter = head;
    while (iter!=NULL)
    {
        iter->kaydetOgrenciBilgi();
        iter = iter->next;
    }
    cout<<"\nÖğrenciler Diske Kaydedildi!\n";
}
