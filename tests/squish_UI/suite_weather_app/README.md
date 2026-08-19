# Squish Setup și Testare Automată pentru aplicația Qt

## Configurare inițială

Am descărcat și instalat versiunea de **Squish** compatibilă cu versiunea de **Qt** utilizată de aplicație.

După pornirea Squish:

- Am creat o nouă **Test Suite**.
- Am configurat **AUT (Application Under Test)** indicând executabilul aplicației.
- Din **Suite Settings**, am asociat AUT-ul suitei de teste.
- Am configurat pornirea automată a aplicației la rularea testelor.

## Pregătirea executabilului Qt Quick

Pentru ca executabilul aplicației Qt Quick să poată fi pornit de Squish, este necesară rularea utilitarului `windeployqt`.

Se deschide consola Qt aferentă versiunii utilizate (ex. din butonul Start `Qt\6.11.1\mingw_64`) și se execută comanda din directorul unde se află executabilul aplicației:

```cmd
windeployqt appWeatherInfoMVVM.exe
```

După acest pas, aplicația poate fi pornită atât din Command Prompt, cât și direct de către Squish.

## Crearea și rularea testelor

Pentru a crea un test:

1. Se creează un nou **Test Case**.
2. Se apasă **Record**.
3. Se execută acțiunile dorite în aplicație.
4. Squish generează automat codul necesar.

La rularea testului, acțiunile înregistrate sunt executate automat, iar rezultatul va fi **Success** sau **Failure**, în funcție de comportamentul aplicației.

### Recomandări

- Adăugați verificări suplimentare folosind **Object Inspect** pentru a valida valorile obiectelor și stările acestora.
- Definiți proprietatea `objectName` în QML pentru elementele care trebuie identificate în teste.
- Mențineți un **Object Map** organizat și folosiți nume sugestive pentru obiecte.

Exemplu:

```text
weatherForecastSelectLocationButton_2
```

poate fi redenumit în:

```text
SelectLocationBtn
```

---

## Dificultăți întâmpinate

### Identificarea obiectelor după `objectName`

Inițial am încercat identificarea obiectelor doar după proprietatea `objectName`, însă acest lucru nu este suficient.

Este necesară cel puțin combinația dintre `objectName` și `type`:

```javascript
var listView = waitForObject("{name='countiesListView' type='QQuickListView'}");
```

În anumite cazuri este necesară și specificarea containerului:

```javascript
var countyFoundObj = waitForObject({
    "container": names.weatherForecastOverlay,
    "objectName": "county_Alba",
    "type": "Button"
});
```

`names` reprezintă obiectul exportat de Squish care conține elementele definite în **Object Map**.

Pentru a vedea toate proprietățile disponibile ale unui obiect, aplicația poate fi rulată în **Debug Mode** din Squish.

După ce obiectul este localizat în arborele de obiecte (**Object Tree**):

1. Selectează obiectul dorit.
2. Apasă click dreapta pe acesta.
3. Alege opțiunea **Copy Real Name**.

### Probleme de sincronizare cu ListView

Am întâmpinat probleme de sincronizare la interacțiunea cu un `ListView` care își expandează elementele la click.

Inițial acestea puteau fi rezolvate doar folosind:

```javascript
snooze()
```

Am încercat și alte metode:

- verificarea proprietății `visible`
- verificarea proprietății `expanded`
- sincronizarea pe baza altor elemente din interfață

Aceste abordări nu au fost suficiente.

Soluția care s-a dovedit fiabilă a fost implementarea unui **retry pentru click-ul care realizează expand-ul**. În anumite situații, elementele listei nu sunt complet randate la primul click, iar repetarea acțiunii rezolvă problema.

---

## Teste implementate

Pentru rularea testelor a fost utilizat argumentul **fake-service**, astfel încât aplicația să folosească date mock și rezultate predictibile.

Au fost implementate și rulate cu succes următoarele teste:

- verificarea populării corecte a listei de județe (`countyList`)
- verificarea actualizării informațiilor meteo după dublu click pe un oraș
- verificarea închiderii dialogului după selectarea unui oraș
- verificarea funcționalității de expand/collapse pentru `ListView`
- executarea a trei actualizări consecutive și verificarea actualizării corecte a label-ului care afișează orașul selectat

## Concluzie

Squish oferă o modalitate rapidă și eficientă de automatizare a testelor pentru aplicațiile Qt. Pentru rezultate stabile și teste ușor de întreținut este recomandată utilizarea consecventă a proprietății `objectName`, organizarea Object Map-ului și tratarea explicită a situațiilor de sincronizare din interfață.