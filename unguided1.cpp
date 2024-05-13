#include <iostream>
#include <string>
using namespace std;
const int MAX_SIZE = 10;

// 2311102034_Rizal Dwi Anggoro

struct Node
{
    string NIM;
    string nama;
    int nilai;
    Node *next;
    Node(string NIM, string nama, int nilai) : NIM(NIM), nama(nama), nilai(nilai), next(nullptr) {}
};

class HashTable
{
private:
    Node **table;

public:
    HashTable()
    {
        table = new Node *[MAX_SIZE]();
    }
    ~HashTable()
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            Node *current = table[i];
            while (current != nullptr)
            {
                Node *temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }
    
    int hash(string NIM)
    {
        int sum = 0;
        for (char c : NIM)
        {
            sum += c;
        }
        return sum % MAX_SIZE;
    }
    
    void insert(string NIM, string nama, int nilai)
    {
        int index = hash(NIM);
        Node *newNode = new Node(NIM, nama, nilai);
        if (table[index] == nullptr)
        {
            table[index] = newNode;
        }
        else
        {
            Node *current = table[index];
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    
    void remove(string NIM)
    {
        int index = hash(NIM);
        Node *current = table[index];
        Node *prev = nullptr;
        while (current != nullptr)
        {
            if (current->NIM == NIM)
            {
                if (prev == nullptr)
                {
                    table[index] = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "NIM " << NIM << " Gak Ada\n";
    }
    
    void searchNIM(string NIM)
    {
        int index = hash(NIM);
        Node *current = table[index];
        while (current != nullptr)
        {
            if (current->NIM == NIM)
            {
                cout << "NIM : " << current->NIM << endl;
                cout << "Nama: " << current->nama << endl;
                cout << "Nilai: " << current->nilai << endl;
                return;
            }
            current = current->next;
        }
        cout << "NIM : " << NIM << " TIDAK ADA" << endl;
    }
    // Searching by range of values (80-90)
    void searchRange()
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            Node *current = table[i];
            while (current != nullptr)
            {
                if (current->nilai >= 80 && current->nilai <= 90)
                {
                    cout << "NIM: " << current->NIM << ", NAMA: " << current->nama << ", Nilai: " << current->nilai << endl;
                }
                current = current->next;
            }
        }
    }
  
    void display()
    {
        cout << "DATA MAHASISWA:\n";
        for (int i = 0; i < MAX_SIZE; i++)
        {
            Node *current = table[i];
            while (current != nullptr)
            {
                cout << "NIM: " << current->NIM << ", NAMA: " << current->nama << ", Nilai: " << current->nilai << endl;
                current = current->next;
            }
        }
    }
};
int main()
{
    HashTable hashTable;
    int menu;
    string NIM, nama;
    int nilai;
    do
    {
        cout << "======Menu======\n";
        cout << "1. TAMBAH DATA\n";
        cout << "2. HAPUS DATAA\n";
        cout << "3. CARI NIM\n";
        cout << "4. CARI RENTANG NILAI (80-90)\n";
        cout << "5. MENAMPILKAN SEMUA DATA\n";
        cout << "6. EXIT\n";
        cout << "PILIH : ";
        cin >> menu;
        cout << "================\n";
        switch (menu)
        {
        case 1:
            cout << "Input NIM: ";
            cin >> NIM;
            cout << "Input Nama: ";
            cin >> nama;
            cout << "Input Nilai: ";
            cin >> nilai;
            hashTable.insert(NIM, nama, nilai);
            break;
        case 2:
            cout << "Input NIM : ";
            cin >> NIM;
            hashTable.remove(NIM);
            break;
        case 3:
            cout << "Input NIM : ";
            cin >> NIM;
            hashTable.searchNIM(NIM);
            break;
        case 4:
            cout << "Data Nilai 80-90: ";
            hashTable.searchRange();
            break;
        case 5:
            hashTable.display();
            break;
        case 6:
            cout << "TY.\n";
            break;
        default:
            cout << "Menu Tidak Ada.\n";
        }
    } while (menu != 6);
    return 0;
}
