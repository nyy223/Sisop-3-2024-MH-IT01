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
