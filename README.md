# Rollenspielhimmel_Tool

## German

Dieses Programm gibt euch die Möglichkeit, ein komplettes Forum zu laden und auf euren PC in eine Textfile zu speichern. Somit habt ihr die Arbeit nicht, absolut jeden Beitrag einzeln speichern zu müssen. Es ist geplant, weitere Features in Zukunft hinzuzufügen. Wenn ihr wünsche habt, schreibt mir hier ein Featurevorschlag oder meldet euch bei den User: **Nora** auf rollenspielhimmel.de (Nein, das bin nicht ich)

## English

This application is addressed to a german website [Rollenspielhimmel](https://rollenspielhimmel.de). So I will write most parts in german. Feel free to use this application and modify it. Short explanation: It fetches posts from a forum (multiple pages possible) and saves it in a textfile.

## Wie funktioniert das Programm?

### Link zum Forum richtig kopieren

Geht auf das Forum, welches ihr herunterladen möchtet.
Wenn euer Link so aussieht, dann müsst ihr auf eine beliebige Seite wechseln.

![](https://media.giphy.com/media/C9x3iVKbEIJmb4EID9/giphy.gif)

### Link richtig einfügen im Programm

Es ist wichtig, dass ihr die Seitenzahl am Ende entfernt, wenn ihr mehrere Seiten herunterladen möchtet.

![](https://media.giphy.com/media/8ehwS1bQANvLlIvd7H/giphy.gif)

## Deployment

Auf dieser GitHub Seite, könnt ihr unter "Releases" die neueste Version als Setup Datei herunterladen und installieren.

## Getting started

### Build with

* [qmake](https://doc.qt.io/qt-5/qmake-manual.html) - Dependency Management
* [Qt](https://www.qt.io/) - Framework used

### Requirements

* Qt 5.12.1 (Probably works with a lower version.) Important: Needs to support QWebEngine
* Windows 10 (Not tested on different systems yet)
* Microsoft Visual C++ Redistributable (x86)

### Installation

Clone the repository and open Qt with RHS_Tool.pro

```
git clone https://github.com/DasEvoli/RSH_Tool.git
```

## Known issues

* Manchmal loggt man sich nicht beim ersten mal ein. 
* Manche Tags werden noch nicht erkannt.

## Authors

* **DasEvoli** (Vinzenz Wetzel)

## License

This project is licensed under the GNU GENERAL PUBLIC LICENSE Version 3 (GPL3)

## Thanks to

* Thank you to the servers of Rollenspielhimmel.de for not banning me because I requested your website too many times.
* Thank you TheDarkShadow123 for this Eevee gif. I love it. [Check him out](https://www.deviantart.com/thedarkshadow123)