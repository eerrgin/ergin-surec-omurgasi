# ergin-surec-omurgasi

Ergin Kaplan. Kisisel Linux calismasi. Sistem yoneticisi betigi degil; surec durumunun cekirdegin yazdigi metin arayuzunden okunmasi.

## Ne olculur

`/proc/<pid>/status` icinden:

- `VmRSS`: surece ait, fiziksel bellekte duran sayfalarin yaklasik kilobayti. Sanal adres alani degildir.
- `Threads`: ayni surec kimligi altinda, ayri zamanlanabilen is parcacigi sayisi.
- `voluntary_ctxt_switches`: surecin kendisi bloklanarak islemciyi biraktigi anahtar sayisi (okuma, uyku, kilit).
- `nonvoluntary_ctxt_switches`: zaman dilimi bitince cekirdegin sureci zorla indirdigi anahtar sayisi.

Iki sayacin farki, programin bekledigini mi yoksa islemciyi paylasmak zorunda kaldigini mi gosterir.

## Sozlesme

Ayristirici dosyayi kendisi acmaz; metin alir. Boylece canli `/proc` olmadan sabit bir ornekle test edilir. Canli okuma ayri ve Linux'ta `/proc/self/status` uzerinde duman testidir.

```bash
make test
```
