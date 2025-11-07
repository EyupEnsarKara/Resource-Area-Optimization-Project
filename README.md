# Kaynak Alan Optimizasyon Projesi

## 📋 Proje Hakkında

Bu proje, denizlerde doğal kaynak arama ve çıkarma işlemleri yapan bir şirket için geliştirilmiş bir optimizasyon yazılımıdır. Proje, arama alanlarının en optimal (en karlı veya en az zarar durumu) biçimde belirli boyutlardaki düzgün karesel parçalara bölünmesi ve bu işlem sırasında maliyet-fayda hesaplamalarının yapılması amacıyla tasarlanmıştır.

## 👥 Proje Geliştiricileri

- **Eyüp Ensar Kara** (220201061)
- **Yunus Hanifi Öztürk** (220201083)

## 🎯 Proje Amacı

Proje, öğrencilerin temel programlama ve grafik çizim bilgilerini pekiştirmeyi ve problem çözme becerilerini geliştirmeyi amaçlamaktadır.

## 💻 Programlama Dili ve Teknolojiler

- **Programlama Dili:** C
- **Grafik Kütüphanesi:** OpenGL (GLUT)
- **HTTP İstekleri:** libcurl
- **Derleyici:** Visual Studio (MSVC)

## 📦 Gereksinimler

### Kütüphaneler
- **OpenGL:** NuGet paket yöneticisi ile `nupengl.core` paketi
- **libcurl:** vcpkg paket yöneticisi ile kurulum

### Sistem Gereksinimleri
- Windows işletim sistemi
- Visual Studio (C++ geliştirme araçları)
- İnternet bağlantısı (koordinat verilerini çekmek için)

## 🚀 Kurulum

1. Projeyi klonlayın veya indirin
2. Visual Studio'da `Prolab1-1.project.sln` dosyasını açın
3. NuGet paket yöneticisi ile `nupengl.core` paketini yükleyin
4. vcpkg ile `libcurl` kütüphanesini yükleyin
5. Projeyi derleyin ve çalıştırın

## 📖 Proje Aşamaları

### 1. AŞAMA: Sismik Araştırma

Bu aşama, kaynak arama şirketinin sismik araştırma ayağını oluşturmaktadır. Verilen koordinat noktalarını birleştirerek oluşturulan kapalı şeklin alanı, kaynak rezerv miktarının 1/10'una karşılık gelmektedir.

#### Adımlar:

1. **Koordinat Verilerini Okuma**
   - E-destek üzerinden paylaşılacak URL linkindeki web sayfasından değişken sayıda noktanın (x,y) koordinat değerleri okunur
   - Veri formatı: `1B(5,5)(13,12)(8,17)(1,10)(5,5)F`

2. **Kapalı Şekil Çizimi**
   - Okunan noktalar verilen sıraya göre doğrusal olarak birleştirilerek 2 boyutlu kapalı şekil çizilir
   - Koordinat sistemi: (0,0) sol üst köşe, x sağa doğru artar, y aşağı doğru artar

3. **Rezerv Değeri Hesaplama**
   - Çizilen şeklin yüzey alanı hesaplanır
   - Bu değer 10 ile çarpılarak kaynak rezerv değeri elde edilir
   - Alan hesaplama: Şeklin üzerinden geçtiği ve kapladığı tüm birim karelerin toplam sayısı veya matematiksel alan hesaplama yöntemi kullanılabilir

### 2. AŞAMA: Sondaj ve Kaynak Çıkarma

Bu aşama, 1. aşamada yüzey alanları üzerinden rezerv değer miktarı tespit edilen bölgelerde sondaj ve kaynak çıkarma işlemlerini içermektedir.

#### Kısıtlar:

**Kısıt 1: Sondaj Maliyeti**
- Rezerv bölge sınır çizgilerinin her içinden geçtiği ve sınırın içerisinde kalan tüm alanlarda sondaj faaliyeti yapılacaktır
- Bölünmüş karesel alanların toplamının mümkün olduğunca en az olması istenmektedir
- Toplam sondaj maliyeti = (Bölünmüş karesel alanların toplamı) × (Birim sondaj maliyeti)
- Birim sondaj maliyeti: Kullanıcı tarafından 1 ile 10 arasında belirlenebilir

**Kısıt 2: Platform Maliyeti**
- Her bölünmüş karesel alanda çıkarılan kaynakların depolanması için bir platform kurulmalıdır
- Her karesel alanda yalnızca bir platform kurulur
- Platform maliyetleri birbirine eşittir (Birim platform maliyeti kullanıcı tarafından belirlenir)
- Toplam platform sayısının mümkün olduğunca az olması istenmektedir

**Kısıt 3: Karesel Alan Boyutları ve Komşuluk Kuralları**
- Bölünmüş karesel alanların boyutları: **1×1, 2×2, 4×4, 8×8** veya en fazla **16×16** olabilir
- Her karesel alanın sınır komşuları, kendisinden bir boyut büyük veya bir boyut küçük olmalıdır
  - Örnek: 4×4 karesel alanın komşuları 2×2 veya 8×8 olabilir, ancak 1×1 veya 16×16 olamaz
- Sadece köşe noktaları sınır sayılmaz
- Bir karesel alan aynı anda yalnızca tek bir rezerv bölgesini tamamen kapsayabilir, birden fazla rezerv bölgesini kapsayamaz

## 🎮 Kullanım

### Program Başlatma

Program çalıştırıldığında kullanıcıdan şu bilgiler istenir:

1. **Satır Numarası:** Hangi satırdaki koordinat noktalarının çizileceği
2. **Birim Sondaj Maliyeti:** 1-10 arası bir değer
3. **Birim Platform Maliyeti:** 0 veya pozitif bir değer

### Ekranlar

Program iki ayrı çizim ekranı sunar:

#### Ekran 1: Rezerv Alanı Görüntüleme
- Kullanıcının seçtiği satırdaki noktalardan oluşan rezerv bölgesi çizilir
- Rezerv değeri hesaplanır ve gösterilir
- **Klavye:** `1` tuşu ile bu ekrana geçiş yapılır

#### Ekran 2: Optimize Edilmiş Bölümleme
- Rezerv alanı, kısıtlar göz önünde bulundurularak optimal şekilde karesel parçalara bölünür
- Farklı boyuttaki karesel alanlar farklı renklerle gösterilir:
  - **1×1:** Açık yeşil
  - **2×2:** Turuncu
  - **4×4:** Sarı
  - **8×8:** Yeşil
  - **16×16:** Mavi
- **Klavye:** `2` tuşu ile bu ekrana geçiş yapılır

### Çıktı Bilgileri

İkinci ekranda aşağıdaki bilgiler konsola yazdırılır:

- **Toplam Platform Sayısı**
- **Toplam Sondaj Alanı** (birim kare cinsinden)
- **Toplam Platform Maliyeti**
- **Toplam Sondaj Maliyeti**
- **Toplam Maliyet** (Platform + Sondaj)
- **Kar Miktarı** (Rezerv Değeri - Toplam Maliyet)

## 📊 Örnek Veri Formatı

Web sayfasından okunan veri formatı:

```
1B(5,5)(13,12)(8,17)(1,10)(5,5)F
2B(20,20)(30,20)(20,40)(10,40)(20,20)(40,22)(50,32)(30,32)(40,22)F
```

- Her satır bir veya daha fazla kapalı çokgen içerebilir
- Çokgenler aynı koordinatla başlayıp biterek ayrılır
- Format: `[SatırNo]B[Koordinatlar]F`

## 🖼️ Örnek Proje Çıktıları

![image](https://github.com/yunushanifi84/Resource-Area-Optimization-Project/assets/69470694/86bad714-9b45-4d66-b362-0cba7e4b5c0c)
![image](https://github.com/yunushanifi84/Resource-Area-Optimization-Project/assets/69470694/975311ac-b85f-4db4-9b3a-7ca75270b317)
![image](https://github.com/yunushanifi84/Resource-Area-Optimization-Project/assets/69470694/3a3292ba-7160-4c29-8991-07e97c1fa78f)
![image](https://github.com/yunushanifi84/Resource-Area-Optimization-Project/assets/69470694/0738f9bd-deb2-46c0-a4f6-4f920f754ff2)
![image](https://github.com/yunushanifi84/Resource-Area-Optimization-Project/assets/69470694/99bfd2ae-4e72-49e7-b553-297ef9c1cdae)
![image](https://github.com/yunushanifi84/Resource-Area-Optimization-Project/assets/69470694/8c613194-f9ba-4350-b266-10a5f738a0fe)

## 🔧 Teknik Detaylar

### Ana Fonksiyonlar

- **Koordinat İşleme:** Web'den veri çekme, parse etme ve çokgen oluşturma
- **Grafik Çizimi:** OpenGL ile 2D çizim ve renklendirme
- **Alan Hesaplama:** Çokgen içi nokta kontrolü ve alan hesaplama
- **Optimizasyon:** Dinamik programlama ile optimal karesel bölümleme
- **Maliyet Hesaplama:** Platform ve sondaj maliyetlerinin hesaplanması

### Veri Yapıları

- `Point`: Koordinat noktaları
- `polygon`: Çokgen bilgileri ve alan hesaplamaları
- `line`: Satır bazlı çokgen grupları
- `ResourceArea`: Karesel alan matrisi

## 📝 Lisans

Bu proje Kocaeli Üniversitesi Bilgisayar Mühendisliği Bölümü BLM209 Programlama Lab. I dersi kapsamında geliştirilmiştir.

## 📧 İletişim

Proje hakkında sorularınız için:
- Eyüp Ensar Kara
- Yunus Hanifi Öztürk

---

**Not:** Bu proje eğitim amaçlı geliştirilmiştir.
