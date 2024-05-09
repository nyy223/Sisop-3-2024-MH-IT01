# Laporan Resmi Praktikum Sisop-3-2024-MH-IT01

## Anggota
### Nayla Raissa Azzahra (5027231054)
### Ryan Adya Purwanto (5027231046)
### Rafael Gunawan (5027231019)

## Ketentuan
### Struktur repository seperti berikut : 
	—soal_1:
		— auth.c
		— rate.c
		— db.c
                                    
	—soal_2:
		— dudududu.c
				
	—soal_3:
		— actions.c
		— driver.c
		— paddock.c
				
	—soal_4:
		— client/
			— client.c 
		— server/
			— server.c
     
## Soal 1
> Rafael (5027231019)
### Soal
#### Pada zaman dahulu pada galaksi yang jauh-jauh sekali, hiduplah seorang Stelle. Stelle adalah seseorang yang sangat tertarik dengan Tempat Sampah dan Parkiran Luar Angkasa. Stelle memulai untuk mencari Tempat Sampah dan Parkiran yang terbaik di angkasa. Dia memerlukan program untuk bisa secara otomatis mengetahui Tempat Sampah dan Parkiran dengan rating terbaik di angkasa. Programnya berbentuk microservice sebagai berikut:
#### a). Dalam auth.c pastikan file yang masuk ke folder new-entry adalah file csv dan berakhiran  trashcan dan parkinglot. Jika bukan, program akan secara langsung akan delete file tersebut. 
#### Contoh dari nama file yang akan diautentikasi:
    belobog_trashcan.csv
    osaka_parkinglot.csv
#### b). Format data (Kolom)  yang berada dalam file csv adalah seperti berikut:
![image](https://github.com/nyy223/Sisop-3-2024-MH-IT01/assets/151918510/fada6ee5-a6a3-4f3a-8235-efb5fba86575)
#### atau
![image](https://github.com/nyy223/Sisop-3-2024-MH-IT01/assets/151918510/167b5f84-f0ef-41c4-82c8-ac844f892946)
#### c). File csv yang lolos tahap autentikasi akan dikirim ke shared memory. 
#### d). Dalam rate.c, proses akan mengambil data csv dari shared memory dan akan memberikan output Tempat Sampah dan Parkiran dengan Rating Terbaik dari data tersebut.
![image](https://github.com/nyy223/Sisop-3-2024-MH-IT01/assets/151918510/3343294c-68bb-4f30-a163-ff018a2d0dc6)
#### e). Pada db.c, proses bisa memindahkan file dari new-data ke folder microservices/database, WAJIB MENGGUNAKAN SHARED MEMORY.
#### f). Log semua file yang masuk ke folder microservices/database ke dalam file db.log dengan contoh format sebagai berikut:
    [DD/MM/YY hh:mm:ss] [type] [filename]
    ex : [07/04/2024 08:34:50] [Trash Can] [belobog_trashcan.csv]

#### Contoh direktori awal:
    ├── auth.c
    ├── microservices
    │   ├── database
    │   │   └── db.log
    │   ├── db.c
    │   └── rate.c
    └── new-data
        ├── belobog_trashcan.csv
        ├── ikn.csv
        └── osaka_parkinglot.csv

#### Contoh direktori akhir setelah dijalankan auth.c dan db.c:
    ├── auth.c
    ├── microservices
    │   ├── database
    │   │   ├── belobog_trashcan.csv
    │   │   ├── db.log
    │   │   └── osaka_parkinglot.csv
    │   ├── db.c
    │   └── rate.c
    └── new-data

## Soal 3
> Rafael (5027231019)
### Soal
#### Shall Leglerg🥶 dan Carloss Signs 😎 adalah seorang pembalap F1 untuk tim Ferrari 🥵. Mobil F1 memiliki banyak pengaturan, seperti penghematan ERS, Fuel, Tire Wear dan lainnya. Pada minggu ini ada race di sirkuit Silverstone. Malangnya, seluruh tim Ferrari diracun oleh Super Max Max pada hari sabtu sehingga seluruh kru tim Ferrari tidak bisa membantu Shall Leglerg🥶 dan Carloss Signs 😎 dalam race. Namun, kru Ferrari telah menyiapkan program yang bisa membantu mereka dalam menyelesaikan race secara optimal. Program yang dibuat bisa mengatur pengaturan - pengaturan dalam mobil F1 yang digunakan dalam balapan. Programnya ber ketentuan sebagai berikut:
#### a). Pada program actions.c, program akan berisi function function yang bisa di call oleh paddock.c
#### b). Action berisikan sebagai berikut:
    - Gap [Jarak dengan driver di depan (float)]: Jika Jarak antara Driver dengan Musuh di depan adalah < 3.5s maka return Gogogo, jika jarak > 3.5s dan 10s return Push, dan jika jarak > 10s maka return Stay out of trouble.
    - Fuel [Sisa Bensin% (string/int/float)]: Jika bensin lebih dari 80% maka return Push Push Push, jika bensin di antara 50% dan 80% maka return You can go, dan jika bensin kurang dari 50% return Conserve Fuel.
    - Tire [Sisa Ban (int)]: Jika pemakaian ban lebih dari 80 maka return Go Push Go Push, jika pemakaian ban diantara 50 dan 80 return Good Tire Wear, jika pemakaian di antara 30 dan 50 return Conserve Your Tire, dan jika pemakaian ban kurang dari 30 maka return Box Box Box.
    - Tire Change [Tipe ban saat ini (string)]: Jika tipe ban adalah Soft return Mediums Ready, dan jika tipe ban Medium return Box for Softs.
#### Contoh:
		[Driver] : [Fuel] [55%]
		[Paddock]: [You can go]
#### c). Pada paddock.c program berjalan secara daemon di background, bisa terhubung dengan driver.c melalui socket RPC.
#### d). Program paddock.c dapat call function yang berada di dalam actions.c.
#### e). Program paddock.c tidak keluar/terminate saat terjadi error dan akan log semua percakapan antara paddock.c dan driver.c di dalam file race.log
    Format log:
    [Source] [DD/MM/YY hh:mm:ss]: [Command] [Additional-info]
    ex :
    [Driver] [07/04/2024 08:34:50]: [Fuel] [55%]
    [Paddock] [07/04/2024 08:34:51]: [Fuel] [You can go]
#### f). Program driver.c bisa terhubung dengan paddock.c dan bisa mengirimkan pesan dan menerima pesan serta menampilan pesan tersebut dari paddock.c sesuai dengan perintah atau function call yang diberikan.
#### g). Jika bisa digunakan antar device/os (non local) akan diberi nilai tambahan.
#### h). Untuk mengaktifkan RPC call dari driver.c, bisa digunakan in-program CLI atau Argv (bebas) yang penting bisa send command seperti poin B dan menampilkan balasan dari paddock.c
    ex:
    Argv: 
    ./driver -c Fuel -i 55% 
    in-program CLI:
    Command: Fuel
    Info: 55%

#### Contoh direktori 😶‍🌫️:
    ├── client
    │   └── driver.c
    └── server
        ├── actions.c
        ├── paddock.c
        └── race.log

## Soal 4
> Nayla 5027231054

Soal nomor 4 menyuruh kita untuk membuat program untuk menghubungkan client dan server melalui socket. Client berfungsi sebagai pengirim pesan dan menerima pesan dari server, sedangkan server berfungsi sebagai penerima pesan dari client dan hanya menampilkan pesan perintah client saja.  

Ketentuan command untuk dikirimkan ke server dan ditampilkan hasilnya di client adalah:
* Menampilkan seluruh judul
* Menampilkan judul berdasarkan genre
* Menampilkan judul berdasarkan hari
* Menampilkan status berdasarkan berdasarkan judul
* Menambahkan anime ke dalam file myanimelist.csv
* Melakukan edit anime berdasarkan judul
* Melakukan delete berdasarkan judul
* Selain command yang diberikan akan menampilkan tulisan “Invalid Command”
* Jika user mengirim pesan “exit” dari sisi client, maka koneksi antara server dan client akan terputus

Hasil dari penambahan, perubahan, dan penghapusan pada anime akan dicatat di sebuah file log yang bernama "change.log" dengan formatnya adalah [date] [type] [message]. Contoh: 
1. [29/03/24] [ADD] Kanokari ditambahkan.
2. [29/03/24] [EDIT] Kamis,Comedy,Kanokari,completed diubah menjadi Jumat,Action,Naruto,completed.
3. [29/03/24] [DEL] Naruto berhasil dihapus.

Hasil akhir :
```bash
soal_4/
    ├── change.log
    ├── client/
    │   └── client.c
    ├── myanimelist.csv
    └── server/
        └── server.c
```
### Penyelesaian
1. Membuat folder "soal_4". Lalu membuat folder "server" dan "client" di dalam folder "soal_4".
2. Download file csv yang bernama "myanimelist.csv" dari link yang ada pada soal dengan command
```bash
wget -O /home/nayla/soal_4/myanimelist.csv 'https://drive.google.com/uc?export=download&id=10p_kzuOgaFY3WT6FVPJIXFbkej2s9f50'
```
3. Masuk ke folder "client", lalu membuat sebuah file bernama "client.c"
### client.c
```bash
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8080
```
Di bagian ini, beberapa header file yang diperlukan untuk operasi input-output, manipulasi string, operasi socket, dan manipulasi alamat IP telah di-include. Selain itu, port standar yang akan digunakan adalah 8080.
##### sendCommand()
```bash
void sendCommand(int sock, char *command) {
    send(sock, command, strlen(command), 0);
}
```
Ini adalah fungsi yang digunakan untuk mengirim perintah dari client ke server melalui socket. Fungsi send() digunakan untuk mengirim data melalui koneksi socket.
##### receiveResponse()
```bash
void receiveResponse(int sock) {
    char buffer[1024] = {0};
    if (recv(sock, buffer, 1024, 0) < 0) {
        printf("\nRead error\n");
        return;
    }
    printf("Server:\n%s\n", buffer);
}
```
Fungsi receiveResponse() digunakan untuk menerima respons dari server setelah mengirimkan perintah. Data yang diterima dari server disimpan dalam buffer dan kemudian dicetak.
##### fungsi main
```bash
int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char command[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
```
Akan dibuat sebuah socket baru menggunakan fungsi socket(). Jika pembuatan socket gagal, program akan mencetak pesan kesalahan dan keluar.
```bash
 if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
```
Fungsi connect() digunakan untuk menghubungkan socket client ke server.
```bash
    while (1) {
        printf("Enter command (type 'exit' to quit): ");
        fgets(command, sizeof(command), stdin);

        sendCommand(sock, command);

        if (strcmp(command, "exit\n") == 0) {
            printf("Exiting...\n");
            break;
        }

        receiveResponse(sock);
    }

    close(sock);

    return 0;
}
```
Pada bagian ini, program masuk ke dalam loop tak terbatas. Pengguna diminta untuk memasukkan perintah. Perintah tersebut dikirim ke server menggunakan fungsi sendCommand(). Jika perintah adalah "exit", program keluar dari loop. Setelah mengirim perintah, program menerima respons dari server menggunakan fungsi receiveResponse() dan mencetaknya ke layar. Setelah keluar dari loop, koneksi socket ditutup dan program selesai.
4. Masuk ke folder "server", lalu membuat sebuah file bernama "server.c"
### server.c
```bash
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
```
Baris ini mengimpor beberapa library standar yang dibutuhkan untuk berbagai operasi termasuk manipulasi string (<string.h>), alokasi memori (<stdlib.h>), operasi file (<stdio.h>), dan operasi soket (<sys/socket.h> dan <netinet/in.h>). Juga, terdapat <time.h> untuk manipulasi waktu.
```bash
#define PORT 8080
#define MAX_ANIME_COUNT 1000
#define MAX_FIELDS 4 
#define MAX_FIELD_LENGTH 100
#define CSV_FILENAME "/home/nayla/soal_4/myanimelist.csv"
#define CHANGE_LOG_FILENAME "/home/nayla/soal_4/change.log"
```
Di sini, konstanta-konstanta yang digunakan dalam program didefinisikan. Yaitu port yang akan digunakan oleh server (PORT), maksimum jumlah anime yang bisa disimpan (MAX_ANIME_COUNT), maksimal jenis entri anim yang bisa ditampilkan (MAX_FIELDS), maksimal karakter dalam string yang digunakan untuk menyimpan informasi anime (MAX_FIELD_LENGTH), path dari file csv (CSV_FILENAME), dan path dari file log (CHANGE_LOG_FILENAME). 
```bash
typedef struct {
    char day[MAX_FIELD_LENGTH];
    char genre[MAX_FIELD_LENGTH];
    char title[MAX_FIELD_LENGTH];
    char status[MAX_FIELD_LENGTH];
} Anime;
```
Ini adalah definisi struktur Anime yang digunakan untuk merepresentasikan setiap entri anime dalam daftar. Setiap anime memiliki atribut day, genre, title, dan status.
##### readCSV()
```bash
void readCSV() {
    FILE *file = fopen(CSV_FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    
    char line[MAX_FIELDS * MAX_FIELD_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%[^,],%s", animeList[animeCount].day, animeList[animeCount].genre, animeList[animeCount].title, animeList[animeCount].status);
        animeCount++;
    }
    fclose(file);
}
```
Fungsi readCSV() bertanggung jawab untuk membaca data dari file CSV dan menyimpannya dalam array animeList. 
* Pertama, file csv akan dibuka dalam mode baca ("r") menggunakan fungsi fopen(). Jika file tidak dapat dibuka, program akan mencetak pesan kesalahan dan keluar dengan status kesalahan menggunakan exit(EXIT_FAILURE).
* Setelah itu, program membaca setiap baris dari file CSV satu per satu dan menyimpannya dalam array line. Setiap baris yang dibaca diproses menggunakan sscanf(). %[^,] digunakan untuk membaca setiap karakter sampai karakter koma ,, dan %s untuk membaca string hingga bertemu dengan spasi atau newline.
* Setelah membaca dan memproses satu baris, animeCount ditingkatkan untuk menunjukkan jumlah anime yang sudah dibaca.
* Setelah selesai membaca semua baris, file CSV ditutup dengan menggunakan fclose().
##### writeToChangeLog
```bash
void writeToChangeLog(char *type, char *message) {
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    char date_str[20];
    strftime(date_str, sizeof(date_str), "[%d/%m/%y]", tm_now);

    FILE *file = fopen(CHANGE_LOG_FILENAME, "a");
    if (file == NULL) {
        printf("Error opening change log file.\n");
        return;
    }

    fprintf(file, "%s [%s] %s\n", date_str, type, message);
    fclose(file);
}
```
Fungsi writeToChangeLog digunakan untuk menulis pesan ke file log perubahan.
* Variabel time_t now digunakan untuk menampung waktu saat ini dalam detik.
* Fungsi localtime digunakan untuk mengonversi waktu dalam format time_t menjadi struktur tm yang berisi informasi waktu lokal seperti tahun, bulan, hari, jam, dan lain-lain.
* Variabel date_str adalah array karakter yang akan digunakan untuk menyimpan string tanggal dalam format tertentu.
* Fungsi strftime digunakan untuk memformat waktu dalam struktur tm menjadi format [dd/mm/yy] dan disimpan dalam variabel date_str.
* Fungsi fopen digunakan untuk membuka file log perubahan dalam mode "a" (append), yang berarti data akan ditambahkan ke akhir file tanpa menghapus konten yang sudah ada. Jika file tidak dapat dibuka, maka akan muncul pesan kesalahan.
* Fungsi fprintf digunakan untuk menuliskan format tertentu ke file. Di sini, data yang dituliskan adalah tanggal (date_str), jenis perubahan (type), dan pesan perubahan (message). Setelah selesai menulis, file ditutup dengan fungsi fclose.
##### sendAnimeList()
```bash
void sendAnimeList(int new_socket) {
    char response[1024] = {0};
    for (int i = 0; i < animeCount; i++) {
        strcat(response, animeList[i].title);
        strcat(response, "\n");
    }
    send(new_socket, response, strlen(response), 0);
}
```
Fungsi sendAnimeList() bertujuan untuk mengirim daftar judul anime kepada klien yang terhubung ke socket baru (new_socket). 
* Variabel response digunakan untuk menyimpan daftar judul anime yang akan dikirimkan ke klien.
* Fungsi ini menggunakan loop for untuk mengiterasi melalui setiap entri anime dalam animeList. Setiap judul anime akan ditambahkan ke response menggunakan fungsi strcat(), yang digunakan untuk menggabungkan string.
* Setelah response diisi dengan semua judul anime, fungsi send() digunakan untuk mengirimkan data tersebut melalui socket kepada klien.
##### SendAnimeByGenre()
```bash
void SendAnimeByGenre(char *buffer, int new_socket) {
    char *genrePtr = strstr(buffer, "genre ");
    if (genrePtr != NULL) {
        genrePtr += strlen("genre ");

        char genre[MAX_FIELD_LENGTH];
        sscanf(genrePtr, "%[^\n]", genre);

        char response[1024] = {0};
        for (int i = 0; i < animeCount; i++) {
            if (strstr(animeList[i].genre, genre) != NULL) {
                strcat(response, animeList[i].title);
                strcat(response, "\n");
            }
        }
        send(new_socket, response, strlen(response), 0);
    } else {
        send(new_socket, "Invalid Command", strlen("Invalid Command"), 0);
    }
}
```
Fungsi SendAnimeByGenre() digunakan untuk mengirim daftar judul anime berdasarkan genre yang diminta oleh klien.
* Pertama, fungsi mencari substring "genre " dalam buffer menggunakan fungsi strstr(). Jika ditemukan, pointer ke lokasi tersebut disimpan dalam genrePtr.
* Selanjutnya, genre dari perintah diekstrak menggunakan sscanf() dengan format %[^\n], yang mengambil karakter sampai menemukan karakter newline. Penggunaan %[^\n] memungkinkan agar genre yang dimasukkan bisa terdiri lebih dari satu kata, misalnya genre "Slice of Life". Genre yang diekstrak disimpan dalam array genre.
* Setelah mendapatkan genre, fungsi membuat string respons yang akan diisi dengan daftar judul anime yang sesuai dengan genre yang diminta.
* Fungsi melakukan iterasi melalui array animeList. Untuk setiap anime, jika genre anime tersebut sesuai dengan genre yang diminta, judul anime tersebut ditambahkan ke dalam string respons menggunakan strcat().
* Setelah selesai iterasi, string respons yang sudah terisi dengan daftar judul anime dikirim ke klien melalui socket menggunakan fungsi send()
##### sendAnimeByDay()
```bash
void sendAnimeByDay(int new_socket, char *day) {
    char response[1024] = {0};
    for (int i = 0; i < animeCount; i++) {
        if (strcmp(animeList[i].day, day) == 0) {
            strcat(response, animeList[i].title);
            strcat(response, "\n");
        }
    }
    send(new_socket, response, strlen(response), 0);
}
```
Sama seperti fungsi SendAnimeByGenre(), fungsi sendAnimeByDay() berfungsi untuk mengirim daftar judul anime, tetapi berdasarkan hari. Pertama, fungsi akan membuat variabel response untuk menyimpan daftar judul yang sesuai dengan hari yang dimasukkan oleh client. Fungsi kemudian melakukan iterasi melalui array animeList. Untuk setiap anime, jika hari anime tersebut sesuai dengan hari yang diminta, judul anime tersebut ditambahkan ke dalam string respons menggunakan strcat().
##### sendAnimeByStatus
```bash
void sendAnimeByStatus(int new_socket, char *input) {
    char response[1024] = {0};
    int found = 0;
        for (int i = 0; i < animeCount; i++) {
            if (strcmp(animeList[i].title, input) == 0) {
                strcat(response, animeList[i].status);
                strcat(response, "\n");
                found = 1;
                break;
            } else if (strcmp(animeList[i].status, input) == 0) {
                strcat(response, animeList[i].title);
                strcat(response, "\n");
            }
        }
        send(new_socket, response, strlen(response), 0);
    }
```
Fungsi sendAnimeByStatus() digunakan untuk mengirim daftar judul anime berdasarkan status dan mengirim status dari sebuah judul anime yang diminta oleh client. 
* Fungsi melakukan iterasi melalui array animeList. Di dalam iterasi ini, terdapat dua kondisi.
* Kondisi pertama akan berjalan jika client ingin mengetahui status dari judul anime yang diminta. Jika input yang dimasukkan adalah judul, maka status dari judul tersebut akan ditambahkan ke dalam variabel response menggunakan strcat().
* Kondisi kedua akan berjalan jika client ingin mengetahui judul anime apa saja yang memiliki status sesuai dengan yang diminta. Jika input yang dimasukkan adalah status, maka list judul yang mengalami status tersebut akan ditambahkan ke dalam variabel response menggunakan strcat()
##### addAnime()
```bash
void addAnime(int new_socket,char *animeDetails) {
    if (animeCount >= MAX_ANIME_COUNT) {
        printf("Anime list is full. Cannot add more.\n");
        return;
    }

    char day[MAX_FIELD_LENGTH], genre[MAX_FIELD_LENGTH], title[MAX_FIELD_LENGTH], status[MAX_FIELD_LENGTH];
    sscanf(animeDetails, "%[^,],%[^,],%[^,],%s", day, genre, title, status);

    strcpy(animeList[animeCount].day, day);
    strcpy(animeList[animeCount].genre, genre);
    strcpy(animeList[animeCount].title, title);
    strcpy(animeList[animeCount].status, status);

    animeCount++;
    char logMessage[1024];
    sprintf(logMessage, "%s berhasil ditambahkan", title);
    writeToChangeLog("ADD", logMessage);
    send(new_socket, "anime berhasil ditambahkan.\n", strlen("anime berhasil ditambahkan.\n"), 0);
}
```
Fungsi addAnime bertanggung jawab untuk menambahkan anime baru ke dalam daftar animeList.
* Pertama, fungsi melakukan pemeriksaan apakah daftar anime telah mencapai batas maksimum yang ditentukan (MAX_ANIME_COUNT). Jika daftar telah penuh, maka program akan mencetak pesan kesalahan dan fungsi akan langsung keluar tanpa menambahkan anime baru.
* Selanjutnya, fungsi membaca detail anime yang diberikan dalam parameter animeDetails. Detail anime ini berupa string yang terdiri dari hari, genre, judul, dan status anime yang dipisahkan oleh koma (,). Fungsi sscanf digunakan untuk mem-parsing string tersebut dan menyimpannya ke dalam variabel day, genre, title, dan status.
* Setelah detail anime berhasil diparsing, fungsi akan menyalin nilainya ke dalam atribut animeList[animeCount]. Ini dilakukan dengan menggunakan fungsi strcpy.
* Setelah anime baru berhasil ditambahkan ke dalam animeList, variabel animeCount yang merepresentasikan jumlah anime dalam daftar akan ditambah satu.
* Selanjutnya, sebuah pesan log dibuat untuk merekam penambahan anime baru. Pesan log ini kemudian akan ditulis ke dalam file log perubahan dengan menggunakan fungsi writeToChangeLog.
* Sebuah pesan yang berisi konfirmasi bahwa anime telah berhasil ditambahkan akan dikirim ke client.
##### editAnime()
Fungsi editAnime() bertanggung jawab untuk mengedit detail anime yang sudah ada dalam daftar. Saya akan membahas bagian-bagian dari fungsi ini secara lebih rinci:
```bash
void editAnime(char *animeTitle, char *animeDetails, int new_socket) {
    char *token;
    char oldTitle[MAX_FIELD_LENGTH], oldDay[MAX_FIELD_LENGTH], oldGenre[MAX_FIELD_LENGTH], oldStatus[MAX_FIELD_LENGTH], newDay[MAX_FIELD_LENGTH], newGenre[MAX_FIELD_LENGTH], newTitle[MAX_FIELD_LENGTH], newStatus[MAX_FIELD_LENGTH];
    strcpy(oldTitle, animeTitle); 

    token = strtok(animeDetails, ",");
    if (token != NULL) {
        strcpy(newDay, token);
        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(newGenre, token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(newTitle, token);
                token = strtok(NULL, ",");
                if (token != NULL) {
                    strcpy(newStatus, token);
```
* Pendefinisian beberapa variabel yang akan digunakan dalam fungsi ini.
* Fungsi strtok() digunakan untuk memecah animeDetails menjadi token-token yang dipisahkan oleh koma (,). Ini memungkinkan kita untuk mendapatkan detail baru anime, yaitu newDay, newGenre, newTitle, dan newStatus.
* Variabel oldTitle akan menggunakan judul lama sebagai acuan untuk pencarian judul yang diminta client.
```bash
		int found = 0;
                    for (int i = 0; i < animeCount; i++) {
                        if (strcmp(animeList[i].title, oldTitle) == 0) {
                            found = 1;

                            strcpy(oldDay, animeList[i].day);
                            strcpy(oldGenre, animeList[i].genre);
                            strcpy(oldTitle, animeList[i].title);
                            strcpy(oldStatus, animeList[i].status);
                            
                            strcpy(animeList[i].day, newDay);
                            strcpy(animeList[i].genre, newGenre);
                            strcpy(animeList[i].title, newTitle);
                            strcpy(animeList[i].status, newStatus);
```
Selanjutnya, dilakukan pencarian anime berdasarkan judul lama. Jika ditemukan, atribut-atribut lama disimpan dalam variabel oldDay, oldGenre, oldTitle, dan oldStatus. Setelah itu, nilai-nilai atribut anime tersebut diperbarui dengan nilai-nilai baru yang telah diambil sebelumnya.
```bash
		char logMessage[1024];
                            sprintf(logMessage, "%s,%s,%s,%s diubah menjadi %s,%s,%s,%s", oldDay, oldGenre, oldTitle, oldStatus, newDay, newGenre, newTitle, newStatus);
                            writeToChangeLog("EDIT", logMessage);

                            send(new_socket, "anime berhasil diedit\n", strlen("anime berhasil diedit\n"), 0);
                            break; 
                        }
                    }
```
Selanjutnya, sebuah pesan log dibuat untuk merekam perubahan yang dilakukan. Pesan log ini kemudian ditulis ke file log perubahan dengan menggunakan fungsi writeToChangeLog(). Pesan juga dikirimkan ke klien untuk memberitahu bahwa anime telah berhasil diubah.
```bash
                    if (!found) {
                        char response[1024];
                        sprintf(response, "Anime not found: %s\n", oldTitle);
                        send(new_socket, response, strlen(response), 0);
                    }
                }
            }
        }
    }
}
```
Jika anime dengan judul yang diberikan tidak ditemukan, pesan "Anime not found" dikirimkan ke klien.
##### deleteAnime()
```bash
void deleteAnime(int new_socket,char *animeTitle) {
    for (int i = 0; i < animeCount; i++) {
        if (strcmp(animeList[i].title, animeTitle) == 0) {
            for (int j = i; j < animeCount - 1; j++) {
                strcpy(animeList[j].day, animeList[j + 1].day);
                strcpy(animeList[j].genre, animeList[j + 1].genre);
                strcpy(animeList[j].title, animeList[j + 1].title);
                strcpy(animeList[j].status, animeList[j + 1].status);
            }

            animeCount--;
            char logMessage[1024];
            sprintf(logMessage, "%s berhasil dihapus", animeTitle);
            writeToChangeLog("DEL", logMessage);
            send(new_socket, "anime berhasil dihapus.\n", strlen("anime berhasil dihapus.\n"), 0);
            return;
        }
    }
}
```
Fungsi deleteAnime() bertujuan untuk menghapus sebuah entri anime dari daftar animeList berdasarkan judul anime yang diberikan. 
* Fungsi melakukan iterasi melalui setiap entri dalam animeList menggunakan loop for. Di setiap iterasi, fungsi memeriksa apakah judul anime pada entri saat ini sama dengan animeTitle yang diberikan dengan menggunakan fungsi strcmp().
* Jika judul anime pada entri saat ini sama dengan animeTitle yang diberikan, maka anime tersebut ditemukan dan akan dihapus dari daftar. Untuk melakukan penghapusan, langkah-langkah yang diambil adalah:
  * Loop kedua digunakan untuk menggeser setiap entri anime yang berada setelah entri yang akan dihapus ke posisi sebelumnya. Hal ini dilakukan untuk menutup celah yang terbentuk setelah penghapusan.
  * Setiap atribut entri anime (day, genre, title, status) pada posisi j akan diubah menjadi atribut entri anime pada posisi j + 1. Sehingga, atribut entri anime yang lama akan diabaikan dan sudah tidak lagi berada di dalam list.
  * Setelah loop kedua selesai, jumlah animeCount dikurangi satu untuk mencerminkan penghapusan satu entri anime.
  * Pesan log dibuat menggunakan sprintf() untuk mencatat bahwa anime telah dihapus.
  * Pesan yang memberi tahu bahwa anime telah dihapus dikirim ke klien menggunakan send().
##### fungsi main
Fungsi main merupakan fungsi utama yang berfungsi untuk menjalankan seluruh fungsi yang sudah didefinisikan. 
```bash
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    readCSV();
```
Pertama, fungsi ini akan memanggil fungsi readCSV() untuk membaca data dari file CSV dan menyimpannya dalam array animeList.
```bash
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
}
```
Membuat socket menggunakan socket() system call. Jika gagal, program akan keluar dan menampilkan pesan kesalahan.
```bash
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
}
```
Ini adalah langkah opsional yang memungkinkan penggunaan kembali alamat dan port yang sama setelah socket ditutup. Ini mencegah kesalahan "Alamat sudah digunakan" saat menjalankan ulang server.
```bash
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);

if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
}
```
Menetapkan alamat dan port yang ditentukan ke socket menggunakan bind() system call.
```bash
if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
}
```
Menetapkan server dalam mode mendengarkan menggunakan listen() system call. Parameter kedua menentukan jumlah maksimum koneksi yang dapat ditangani oleh server.
```bash
if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
}
```
Menerima koneksi dari klien menggunakan accept() system call. Ini akan membuat socket baru untuk berkomunikasi dengan klien yang terhubung.
```bash
    while (1) {
        valread = read(new_socket, buffer, 1024);
        if (valread < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Received command from client: %s", buffer);

        if (strncmp(buffer, "tampilkan", 9) == 0) {
            sendAnimeList(new_socket);
        } else if (strncmp(buffer, "genre", 5) == 0) {
            SendAnimeByGenre(buffer, new_socket);
        } else if (strncmp(buffer, "hari", 4) == 0) {
            char day[MAX_FIELD_LENGTH];
            sscanf(buffer, "hari %s", day);
            sendAnimeByDay(new_socket, day);
        } else if (strncmp(buffer, "status ", 7) == 0) {
            char input[MAX_FIELD_LENGTH];
            sscanf(buffer, "%*s %[^\n]", input);
            sendAnimeByStatus(new_socket, input);
        } else if (strncmp(buffer, "add", 3) == 0) {
            char animeDetails[1024];
            sscanf(buffer, "add %[^\n]", animeDetails);
            addAnime(new_socket,animeDetails);
        } else if (strncmp(buffer, "edit", 4) == 0) {
            char animeTitle[MAX_FIELD_LENGTH], animeDetails[1024];
            sscanf(buffer, "edit %[^,], %[^\n]", animeTitle, animeDetails);
            editAnime(animeTitle, animeDetails,new_socket);
        } else if (strncmp(buffer, "delete", 6) == 0) {
            char animeTitle[MAX_FIELD_LENGTH];
            sscanf(buffer, "delete %[^\n]", animeTitle);
            deleteAnime(new_socket,animeTitle);
        } else {
            send(new_socket, "Invalid Command\n", strlen("Invalid Command\n"), 0);
        }
        memset(buffer, 0, sizeof(buffer));
    }
    close(new_socket);
    close(server_fd);
    return 0;
}
```
Server berada dalam loop yang terus berjalan selama klien terhubung dan tidak mengirimkan perintah "exit". Di dalam loop ini, akan dipanggil funsgi-fungsi yang sudah dibuat sesuai dengan command yang diberikan oleh client. Saat menerima perintah dari klien, server akan mengeksekusi aksi yang sesuai berdasarkan perintah yang diterima. Setelah selesai, socket baru dan socket server ditutup.

