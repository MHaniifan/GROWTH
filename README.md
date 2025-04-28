## GROWTH: Greenhouse Remote Operations With Temperature & Humidity

Proyek ini bertujuan untuk mengembangkan sistem automasi cerdas berbasis Mikrokontroler AVR untuk Smart Farming, menggunakan komponen utama seperti Arduino Mega, sensor YL-69 dan DHT-11, serta pompa air dan kipas. Arduino Mega bertindak sebagai mikrokontroler utama yang mengontrol komunikasi antar sensor dan aktuator, memungkinkan pemantauan dan pengontrolan secara real-time. Sistem ini menggunakan Timer pada AVR untuk menjaga sinkronisasi waktu, dan Interrupt untuk menyalakan Pompa Air ketika kelembaban dibawah batas.

Pompa Air akan menyala setiap jadwal penyiraman yang sudah ditentukan. Dimana jadwal penyiraman dan lama pompa menyala, diatur pada GUI pada Komputer yang terhubung ke Mikrokontroler menggunakan komunikasi UART. Untuk Kipas akan menyala setiap suhu telah melewati batas yang ditentukan, dimana batas suhunya dapat diatur pada GUI.

Dengan menggunakan UART, seluruh data dari sensor-sensor ini dikirimkan ke Komputer. Memungkinkan petani untuk memantau penggunaan energi dan kondisi lingkungan secara langsung dari Komputer. Sistem ini dirancang untuk meningkatkan efisiensi energi, hasil produksi, serta dapat mengurangi kerugian dengan mengotomatiskan berbagai fungsi dan memberikan kendali yang lebih fleksibel.

## Supported By :
>- Dosen Pengampu : Akhmad Hendriawan ST., MT. (NIP.197501272002121003)
>- Mata kuliah : Mikrokontroler
>- Program Studi : Sarjana Terapan Teknik Elektronika
>- Politeknik Elektronika Negeri Surabaya<br> 