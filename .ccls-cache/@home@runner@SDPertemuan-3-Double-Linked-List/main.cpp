#include <iostream>
#include <string>

using namespace std;

typedef struct{
  string nim;
  string nama;
  string nilai;
}nilaiMatkul;

typedef struct{
  nilaiMatkul kontainer;
  int prev;
  int next;
}elemen;

typedef struct{
  int first;
  int tail;
  elemen data[10];
}list;

void createList(list *L){

  (*L).first=-1;
  (*L).tail=-1;
  int i;

  for (i=0;i<=10;i++){
    /*proses menginisialisasi isi array*/
    (*L).data[i].prev=-2;
    (*L).data[i].next=-2;
  }
}

int countElement(list L){
  int hasil = 0;
  if(L.first !=-1){
    /*list tidak kosong*/
    int bantu;
    
    /*inisialisasi*/
    bantu = L.first;
    while(bantu !=-1){
      /*proses*/
      hasil = hasil +1;

      /*iterasi*/
      bantu = L.data[bantu].next;
    }
  }
  return hasil;
}

int emptyElement(list L){
  int hasil = -1;
  
  if(countElement(L) < 10){
   
    bool ketemu = false;
    
    int i = 0;
    while((ketemu == false) && (i <= 10)){
      if(L.data[i].next == -2){
        hasil = i;
        ketemu = true;
      }
      else{
        i = i +1;
      }
    }
  }
  return hasil;
}

void addFirst(string nim, string nama, string nilai, list *L){

  if(countElement(*L)<10){
    int baru = emptyElement(*L);
    (*L).data[baru].kontainer.nim = nim;
    (*L).data[baru].kontainer.nama = nama;
    (*L).data[baru].kontainer.nilai = nilai;

    if((*L).first == -1){
      /*jika list kosong*/
      (*L).data[baru].next = -1;
      (*L).tail = baru;
    }
    else{
      /*jika tidak kosong*/
      (*L).data[baru].next = (*L).first;
      (*L).data[(*L).first].prev = baru;
    }
    (*L).first = baru;
  }
  else{
    /*proses jika array penuh*/
    cout << "sudah tidak dapat ditambah" << endl;
  }
}

void addAfter(int before,string nim, string nama, string nilai, list *L){

  if((countElement(*L)<10)&&(before !=-1)){
    int baru = emptyElement(*L);
    (*L).data[baru].kontainer.nim = nim;
    (*L).data[baru].kontainer.nama = nama;
    (*L).data[baru].kontainer.nilai = nilai;

    if((*L).data[before].next == -1){
      /*jika before elemen terakhir*/
      (*L).data[baru].next = -1;
      (*L).tail = baru;
    }
    else{
      (*L).data[baru].next = (*L).data[before].next;
      (*L).data[(*L).data[baru].next].prev = baru;
    }
    (*L).data[before].next = baru;
    (*L).data[baru].prev = before;
  }
  else{
    /*proses jika array penuh*/
    cout << "sudah tidak dapat ditambah" << endl;
  }
}

void addLast(string nim, string nama, string nilai, list *L){

  if((*L).first == -1){
      /*jika list masih kosong*/
      addFirst(nim,nama,nilai,L);
    }
    else{
      /*proses jika telah berisi elemen*/
      addAfter((*L).tail,nim,nama,nilai,L);
    }
}

void delFirst(list *L){

  if((*L).first !=-1){
    int hapus = (*L).first;

    if(countElement(*L)==1){
      (*L).first=-1;
      (*L).tail=-1;
    }
    else{
      (*L).first = (*L).data[(*L).first].next;
      (*L).data[(*L).first].prev = -1;
    }
    /*elemen awal sebelumnya dikosongkan*/
    (*L).data[hapus].prev=-2;
    (*L).data[hapus].next=-2;
  }
  else{
    /*proses jika list kosong*/
    cout << "list kosong" << endl;
  }
}

void delAfter(int before,list *L){

  if(before !=-1){
    int hapus = (*L).data[before].next;

    if(hapus !=-1){
      if((*L).data[hapus].next == -1){
        (*L).data[before].next = -1;
        (*L).tail = before;
      }
      else{
        (*L).data[before].next=(*L).data[hapus].next;
        (*L).data[(*L).data[hapus].next].prev = before;
      }
      /*pengkosongan elemen*/
      (*L).data[hapus].prev = -2;
      (*L).data[hapus].next = -2;
    }
  }
}

void delLast(list *L){
  if((*L).first !=-1){
    if(countElement(*L) == 1){
      /*proses jika list hanya berisi satu elemen*/
      delFirst(L);
    }
    else{
      /*elemen sebelum elemen terakhir menjadi elemen terahir*/
      delAfter((*L).data[(*L).tail].prev,L);
    }
  }
  else{
    /*proses jika list kosong*/
    cout << "list kosong" << endl;
  }
}

void printElement(list L){
  if(L.first !=-1){
    /*inisialisasi*/

    int bantu = L.first;
    int i = 1;
    while (bantu !=-1){
      /*proses*/
      cout << "elemen ke: " << i << endl;
      cout << "nim: " << L.data[bantu].kontainer.nim << endl;
      cout << "nama: " << L.data[bantu].kontainer.nama << endl;
      cout << "nilai: " << L.data[bantu].kontainer.nilai << endl;
      cout << "next: " << L.data[bantu].next << endl;
      cout << "---------------" << endl;
      /*iterasi*/
      bantu = L.data[bantu].next;
      i = i + 1;
    }
  }
  else{
    /*proses jika list kosong*/
    cout << "list kosong" << endl;
  }
}

void delAll(list *L){
  int i;
  for(i=countElement(*L);i>=1;i--){
    /*proses menghapus elemen list*/
    delLast(L);
  }
}

int main() {

  list L;
  createList(&L);
  printElement (L);
  cout << "==================" << endl;
  addFirst("136", "Nana", "A", &L);
  addAfter(L.first, "135", "Iza", "A", &L);
  addLast("137", "Rara", "A", &L);
  addLast("138", "Ara", "A", &L);
  printElement (L);
  cout << "==================" << endl;
  delLast(&L);
  //delAfter(L.first, &L);
  //delFirst(&L);
  printElement (L);
  cout << "==================" << endl;

  return 0;
}