#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

// STRUCT
struct korban
{
    string id;
    string username;
    string telp;
    string deposit;
    string winrate;
    string status;
};

// SORTING
void tukar(string &a, string &b) {
    string t = a; a = b; b = t;
}

void tukarKorban(korban &a, korban &b) {
    korban t = a; a = b; b = t;
}

int partition(string arrId[], string arrDeposit[], korban arrKorban[], int low, int high) {
    string pivot = arrDeposit[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (atof(arrDeposit[j].c_str()) <= atof(pivot.c_str())) {
            i++;
            tukar(arrId[i], arrId[j]);
            tukar(arrDeposit[i], arrDeposit[j]);
            tukarKorban(arrKorban[i], arrKorban[j]);
        }
    }

    tukar(arrId[i + 1], arrId[high]);
    tukar(arrDeposit[i + 1], arrDeposit[high]);
    tukarKorban(arrKorban[i + 1], arrKorban[high]);
    return (i + 1);
}

// quick sort
void quick_sort(string arrId[], string arrDeposit[], korban arrKorban[], int low, int high) {
    if (low < high) {
        int pi = partition(arrId, arrDeposit, arrKorban, low, high);
        quick_sort(arrId, arrDeposit, arrKorban, low, pi - 1);
        quick_sort(arrId, arrDeposit, arrKorban, pi + 1, high);
    }
}

// pemasukkan data ke array
void sortKorban()
{
    string id, deposit;

    int size = 50;
    string arrId[50];
    string arrDeposit[50];
    korban arrKorban[50];
    string ignoreHeading;

    ifstream file("data.txt");
    korban k;
    int i = 0;

    getline(file, ignoreHeading);

    while (getline(file, k.id, ';'))
    {
        getline(file, k.username, ';');
        getline(file, k.telp, ';');
        getline(file, k.deposit, ';');
        getline(file, k.winrate, ';');
        getline(file, k.status, '\n');

        arrId[i] = k.id;
        arrDeposit[i] = k.deposit;
        arrKorban[i] = k;
        i++;
    }
    file.close();

    int actualSize = i;

    quick_sort(arrId, arrDeposit, arrKorban, 0, actualSize - 1);

    // Tampilkan hasil
    for (int j = 0; j < actualSize; j++) {
        cout << "============================" << endl;
        cout << "Id          : " << arrKorban[j].id << endl;
        cout << "Username    : " << arrKorban[j].username << endl;
        cout << "No. Telepon : " << arrKorban[j].telp << endl;
        cout << "Deposit     : " << arrKorban[j].deposit << endl;
        cout << "Winrate (%) : " << arrKorban[j].winrate << endl;
        cout << "Status      : " << arrKorban[j].status << endl;
        cout << "============================" << endl;
    }

    system("pause");
    file.close();
}

// SEARCH
void cariKorban()
{
    ifstream file("data.txt");
    korban k;

    char lagi;

    string idCari;

    cin.ignore();
    cout << "Masukkan id yang dicari: ";cin >> idCari;

    while (getline(file, k.id, ';'))
    {
        getline(file, k.username, ';');
        getline(file, k.telp, ';');
        getline(file, k.deposit, ';');
        getline(file, k.winrate, ';');
        getline(file, k.status);

        if (k.id == idCari)
        {
            cout << "Data ditemukan!"<<endl;
            cout << "============================" << endl;
            cout << "Id          : " << k.id << endl;
            cout << "Username    : " << k.username << endl;
            cout << "No. Telepon : " << k.telp << endl;
            cout << "Deposit     : " << k.deposit << endl;
            cout << "Winrate (%) : " << k.winrate << endl;
            cout << "Status      : " << k.status << endl;
            cout << "============================" << endl;
            
            cout << "Cari lagi?(y/n): "; cin >> lagi;
        }
        
    }
    while (true)
    {
        if (lagi == 'y' || lagi == 'Y')
        {
            system("cls");
            cariKorban();
        } else if (lagi == 'n' || lagi == 'N')
        {
            return;
        }
        else
        {
            cout << "Input tidak valid!" << endl;
            system("pause");
        }
                
    }
    
}

// ADD DATA
// mendapatkan id baru
int getNewId() {
    ifstream file("data.txt");
    string line, lastLine;

    if (!file.is_open()) return 1;

    while (getline(file, line)) {
        if (!line.empty()) {
            lastLine = line;
        }
    }
    file.close();

    if (lastLine.empty() || (lastLine[0] >= 'a' && lastLine[0] <= 'z')) {
        return 1;
    }

    size_t pos = lastLine.find(';');
    if (pos != string::npos) {
        string strId = lastLine.substr(0, pos);
        return stoi(strId) + 1;
    }

    return 1;
}

void addKorban() {
    int jumlah;
    cout << "Masukkan jumlah data: "; cin >> jumlah;

    int nextId = getNewId();
    ofstream file("data.txt", ios::app);

    if (!file.is_open()) {
        cout << "File tidak dapat dibuka!" << endl;
    } else {
        korban d;
        for (int i = 0; i < jumlah; i++) {
            cin.ignore();
            cout << "\nInput Data ke-" << i + 1 << " (Otomatis ID: " << nextId << ")" << endl;
            cout << "Username    : "; getline(cin, d.username);
            cout << "No. Telepon : "; getline(cin, d.telp);
            cout << "Winrate (%) : "; cin >> d.winrate;

            file << nextId << ";" << d.username << ";" << d.telp << ";0;" << d.winrate << ";active" << endl;

            cout << endl << "Data ID " << nextId << " berhasil disimpan!" << endl;
            nextId++; 

            system("pause");
        }
        file.close();
    }
}

// TAMPILKAN DATA
void showKorban()
{
    ifstream file("data.txt");
    korban k;

    string ignoreHeadings;

    if (!file.is_open())
    {
        cout<<"File tidak dapat dibuka!"<<endl;
        system("pause");
    } else {
        getline(file, ignoreHeadings);

        while (getline(file, k.id, ';'))
        {
            getline(file, k.username, ';');
            getline(file, k.telp, ';');
            getline(file, k.deposit, ';');
            getline(file, k.winrate, ';');
            getline(file, k.status);

            cout<<"----------------------------------------------------------------------"<<endl;
            cout<<"Id          : "<<k.id<<endl;
            cout<<"Nama        : "<<k.username<<endl;
            cout<<"No. Telepon : "<<k.telp<<endl;
            cout<<"Deposit     : "<<k.deposit<<endl;
            cout<<"Winrate (%) : "<<k.winrate<<endl;
            cout<<"Status      : "<<k.status<<endl;
            cout<<"----------------------------------------------------------------------"<<endl;
        }

        file.close();
        system("pause");
    }
}

// EDIT DATA
void ubahStatus() {
    ifstream readFile("data.txt");
    ofstream writeFile("temp.txt", ios::trunc);

    string id, username, telp, deposit, winrate, status, idCari;
    bool ditemukan = false;

    showKorban();

    if (!readFile.is_open() || !writeFile.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    cout << "Masukkan ID yang ingin diubah: "; cin >> idCari;

    string line;
    if (getline(readFile, line)) {
        writeFile << line << endl;
    }

    // Proses Salin Data ke Temp
    while (getline(readFile, id, ';')) {
        getline(readFile, username, ';');
        getline(readFile, telp, ';');
        getline(readFile, deposit, ';');
        getline(readFile, winrate, ';');
        getline(readFile, status);

        // input data baru
        if (id == idCari) {
            ditemukan = true;
            string newWin, pil;
            cout << "Data ditemukan: " << username << endl;
            cout << "Winrate baru: "; cin >> newWin;
            cout << "Status (1.active / 2.deactive): "; cin >> pil;
            string newStat = (pil == "1") ? "active" : "deactive";

            writeFile << id << ";" << username << ";" << telp << ";" << deposit << ";" << newWin << ";" << newStat << endl;
            cout << "Data korban berhasil ditambahkan." << endl;
            system("pause");
        } else {
            writeFile << id << ";" << username << ";" << telp << ";" << deposit << ";" << winrate << ";" << status << endl;
        }
    }

    readFile.close();
    writeFile.close();

    // menyalin data baru dari temp.txt ke data.txt
    if (ditemukan) {
        ifstream readTemp("temp.txt");
        ofstream writeData("data.txt", ios::trunc);

        while (getline(readTemp, line)) {
            writeData << line << endl;
        }

        readTemp.close();
        writeData.close();
        cout << "Data berhasil diperbarui!" << endl;
    } else {
        cout << "ID tidak ditemukan." << endl;
    }
}

// TAMPILAN MENU
void menu()
{
    int pilihan;

    while (pilihan != 6)
    {
        system("cls");
        cout<<"=== MENU ==="<<endl;
        cout<<"1. Show Korban"<<endl;
        cout<<"2. Add Korban"<<endl;
        cout<<"3. Ubah Status Korban"<<endl;
        cout<<"4. Cari Korban"<<endl;
        cout<<"5. Sort Korban"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"====================="<<endl;
        cout<<"Pilihan: ";cin>>pilihan;

        switch (pilihan)
        {
        case 1:
            system("cls");
            showKorban();
            break;
        case 2:
            system("cls");
            addKorban();
            break;
        case 3:
            system("cls");
            ubahStatus();
            break;
        case 4:
            system("cls");
            cariKorban();
            break;
        case 5:
            system("cls");
            sortKorban();
            break;
        case 6:
            system("cls");
            cout << "Pelajarannya: Jangan Terjerumus ke Judol." << endl;
            cout << "program ini hanya dibuat untuk edukasi anti judol, buka promosi." << endl;
            system("pause");
            break;
        default:
            cout<<"Input tidak valid!"<<endl;
            system("pause");
            break;
        }
    }
    
}

// TAMPILAN AWAL
void tampilanAwal()
{
    cout<<"========================================"<<endl;
    cout<<"      PROGRAM SIMULASI ADMIN JUDOL      "<<endl;
    cout<<"   hanya untuk edukasi, bukan promosi   "<<endl;
    cout<<"========================================"<<endl;

    cin.get();
}

// MAIN
int main(int argc, char const *argv[])
{
    tampilanAwal();
    menu();

    return 0;
}
