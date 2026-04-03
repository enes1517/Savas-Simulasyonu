# ⚔️ Savaş Simülasyonu (Battle Simulation)

Bu proje, C dilinde geliştirilmiş, iki farklı ırkın (İnsanlar ve Orklar) belirli senaryolara göre savaştığı, sonuçların algoritmik olarak hesaplanıp adım adım loglandığı ve **OpenGL (GLUT)** kullanılarak görselleştirildiği bir savaş simülasyonudur.

## 📌 Proje Özellikleri

- **🌐 Dinamik Veri Çekme (cURL):** Kullanıcının seçimine göre (1-10 arası) belirtilen uzak sunuculardan (`yapbenzet.org.tr` veya `bilgisayar.kocaeli.edu.tr`) ilgili savaş senaryosu JSON dosyalarını indirir.
- **📄 Özel JSON Ayrıştırıcı (Custom Parser):** Harici bir kütüphane kullanmadan, standart C kütüphaneleriyle birimler (`unit_types.json`), kahramanlar (`heroes.json`), canavarlar (`creatures.json`) ve araştırmalar (`research.json`) dosyalarından veri okur.
- **🧮 Gelişmiş Savaş Algoritması:** - Toplam saldırı ve savunma güçlerinin hesaplanması.
  - Orantılı hasar dağılımı (Birimlerin savunma ağırlıklarına göre hasar alması).
  - **Yorgunluk Mekaniği:** Her 5 rauntta bir birimlerin güçlerinin %10 düşmesi.
  - Kahraman, Canavar ve Araştırma (Elit eğitim vb.) bonuslarının kritik vuruş ve yüzdelik artışlarla sisteme dahil edilmesi.
- **📊 Detaylı Loglama:** Savaşın her adımı, hasar dağılımları ve kalan can değerleri `savas_sim.txt` dosyasına detaylı olarak yazdırılır.
- **🖥️ 2D Görselleştirme:** OpenGL kullanılarak savaş alanı 20x20 bir grid üzerinde çizilir. Birliklerin sağlık barları, sayıları ve türleri renk kodlarıyla ekrana yansıtılır.

---

## 🛠️ Kullanılan Teknolojiler ve Kütüphaneler

- **C Programlama Dili**
- **libcurl:** Web üzerinden senaryo dosyalarını indirmek için.
- **OpenGL / GLUT:** Savaş alanının 3 farklı aşamasını (Başlangıç, Orta, Son) görselleştirmek için.
- Standart Kütüphaneler: `<stdio.h>`, `<stdlib.h>`, `<string.h>`

---

## 🚀 Kurulum ve Derleme

Projeyi derleyip çalıştırabilmek için sisteminizde **GCC derleyicisi**, **cURL** ve **OpenGL/FreeGLUT** kütüphanelerinin kurulu olması gerekmektedir.

### Gerekli Kurulumlar (Ubuntu/Debian için)
```bash
sudo apt-get update
sudo apt-get install build-essential libcurl4-openssl-dev freeglut3-dev libgl1-mesa-dev
Windows (Visual Studio / MinGW) İçin
cURL ve FreeGLUT kütüphanelerini projenize (Linker ayarlarından) dahil ettiğinizden emin olun.

Not: Kod içerisinde yerel JSON dosyaları için mutlak yollar (Örn: C:\Users\HP\source\...) kullanılmıştır. Kendi bilgisayarınızda çalıştırırken bu dosya yollarını (line 353, 365, vb.) kendi dizin yapınıza göre güncellemeniz gerekmektedir.

Derleme Komutu (Linux/Terminal)
Bash
gcc main.c -o SavasSimulasyonu -lcurl -lGL -lGLU -lglut -lm
🎮 Kullanım
Derlenen programı çalıştırın:

Bash
./SavasSimulasyonu
Konsol ekranında sizden 1 ile 10 arasında bir senaryo seçmeniz istenecektir.

Seçim yapıldıktan sonra ilgili .json dosyası sunucudan indirilir ve simülasyon başlar.

Savaş bitiminde açılan OpenGL penceresinde birimlerin durumunu görmek için klavyenizdeki Boşluk (Space) tuşuna basarak 3 farklı ekran (Savaş Başı, Savaş Ortası, Savaş Sonu) arasında geçiş yapabilirsiniz.

Savaşın tüm detaylı matematiksel dökümünü incelemek için proje dizininde oluşturulan savas_sim.txt dosyasını açabilirsiniz.

🎨 Görselleştirme (Renk Kodları)
Harita üzerindeki birimler şu renklerle temsil edilir:

🔴 Ork Dövüşçüleri (O): Koyu Kırmızı

🔵 Mızrakçılar (M): Mavi

🟠 Varg Binicileri (V): Turuncu

🟡 Troller (T): Zeytin Yeşili

⚪ Kuşatma Makineleri (K): Gri

🟦 Piyade (P): Açık Mavi

🟩 Okçu (A): Yeşil

🟥 Süvari (S): Açık Kırmızı

(Her birimin üzerinde kalan asker sayısı ve birim harfi yer alırken, kutuların üst kısmındaki renkli bar birimin sağlığını temsil eder.)
