# ESP32-LVGL-TFT-UI

## Configuration d'un écran TFT avec LVGL sur ESP32

Ce projet démontre comment configurer et utiliser un écran TFT tactile avec la bibliothèque LVGL (Light and Versatile Graphics Library) sur un microcontrôleur ESP32.

## Matériel nécessaire

- ESP32 (ESP32-WROOM, ESP32-WROVER, ou autre variante)
- Écran TFT compatible (ILI9341, ST7789, etc.)
- Contrôleur tactile XPT2046 (si écran tactile)
- Câbles de connexion

## Bibliothèques utilisées

- **TFT_eSPI** : Bibliothèque pour contrôler l'écran TFT
- **LVGL** : Bibliothèque graphique pour créer des interfaces utilisateur
- **XPT2046_Touchscreen** : Bibliothèque pour gérer l'écran tactile

## Configuration de l'écran TFT

### 1. Configuration de TFT_eSPI

La bibliothèque TFT_eSPI nécessite une configuration spécifique pour fonctionner avec votre écran TFT et votre ESP32. Cette configuration se fait dans le fichier `User_Setup.h` ou en utilisant l'un des fichiers de configuration prédéfinis dans le dossier `User_Setups`.

#### Étapes de configuration :

1. Ouvrez le fichier `TFT_eSPI/User_Setup.h`
2. Définissez le pilote d'affichage approprié (par exemple, ILI9341_DRIVER)
3. Configurez les broches SPI ou parallèles selon votre câblage :

```cpp
// Pour ESP32 avec SPI
#define TFT_PARALLEL_8_BIT

// Control pins
#define TFT_CS   20    // GPIO 20 (Chip Select)
#define TFT_DC   19    // GPIO 19 (Data/Command)
#define TFT_RST  14   // GPIO 18 (Reset)

#define TFT_WR   15   // GPIO 17 (Write Strobe)
#define TFT_RD   16    // GPIO 16 (Read Strobe - Si la broche RD de l'écran n'est pas utilisée, connectez-la à 3V3 sur l'écran lui-même)

// 8-bit Data Bus pins (DB0-DB7) - Assurez-vous que le câblage physique correspond à cet ordre!
#define TFT_D0   13    // GPIO 13 (vers DB0 de l'écran)
#define TFT_D1   12    // GPIO 12 (vers DB1 de l'écran)
#define TFT_D2   11    // GPIO 11 (vers DB2 de l'écran)
#define TFT_D3   10    // GPIO 10 (vers DB3 de l'écran)
#define TFT_D4   9     // GPIO 9  (vers DB4 de l'écran)
#define TFT_D5   8     // GPIO 8  (vers DB5 de l'écran)
#define TFT_D6   7     // GPIO 7  (vers DB6 de l'écran)
#define TFT_D7   6     // GPIO 6  (vers DB7 de 
4. Configurez les options d'affichage (rotation, ordre des couleurs, etc.)
5. Sélectionnez les polices à charger

### 2. Configuration de l'écran tactile XPT2046

Si vous utilisez un écran tactile avec contrôleur XPT2046, configurez-le comme suit :

```cpp
// Définition des broches pour le contrôleur tactile
#define T_CS    5  // Chip Select pour le contrôleur tactile
#define T_IRQ   34 // Interruption pour détecter les entrées tactiles
#define T_CLK   18 // Signal d'horloge pour SPI (SCK)
#define T_DIN   23 // Entrée de données (MOSI)
#define T_DOUT  19 // Sortie de données (MISO)

// Initialisation de l'écran tactile
XPT2046_Touchscreen ts(T_CS, T_IRQ);
```

## Configuration de LVGL

### 1. Configuration de base de LVGL

La configuration de LVGL se fait dans le fichier `lv_conf.h`. Voici les paramètres importants à configurer :

```cpp
// Profondeur de couleur : 8 (A8), 16 (RGB565), 24 (RGB888), 32 (XRGB8888)
#define LV_COLOR_DEPTH 16

// Résolution maximale de l'écran
#define LV_HOR_RES_MAX 240
#define LV_VER_RES_MAX 320

// Inverser l'ordre des octets pour RGB565 (dépend de l'interface de l'écran)
#define LV_COLOR_16_SWAP 0
```


## Conseils et astuces

1. **Optimisation de la mémoire** : LVGL peut consommer beaucoup de mémoire. Ajustez les paramètres dans `lv_conf.h` pour optimiser l'utilisation de la mémoire.

2. **Performances** : Pour améliorer les performances :
   - Utilisez un tampon de dessin plus grand si possible
   - Activez le DMA pour les transferts SPI si votre écran le supporte
   - Utilisez une fréquence SPI élevée (par exemple, 40MHz)

3. **Débogage** : Utilisez la console série pour déboguer les problèmes d'initialisation ou de performance.

4. **Gestion de l'alimentation** : Assurez-vous que votre ESP32 et votre écran TFT sont correctement alimentés pour éviter les problèmes de stabilité.
