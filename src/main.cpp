/*
  Titre      : Faire un programme qui va pouvoir déterminer si cable est droit ou croisé
  Auteur     : Boladji ODELOUI
  Date       : 25/02/2025
  Description: Testeur RJ45
  Version    : 0.0.1
*/

#include <Arduino.h>

// Définition des broches pour les 8 fils du câble RJ45
const int pinsTX[] = {2, 3, 4, 5, 6, 7, 8, 9};         // Broches pour l'émetteur
const int pinsRX[] = {10, 11, 12, 13, A0, A1, A2, A3}; // Broches pour le récepteur

void setup()
{
  Serial.begin(9600);

  // Configuration des broches TX en sortie et RX en entrée
  for (int i = 0; i < 8; i++)
  {
    pinMode(pinsTX[i], OUTPUT);
    pinMode(pinsRX[i], INPUT_PULLUP);
  }
}

void loop()
{
  bool isStraight = true;
  bool isCrossed = true;

  for (int i = 0; i < 8; i++)
  {
    // Activer une broche TX à la fois
    digitalWrite(pinsTX[i], LOW);
    delay(10);

    // Vérifier les connexions
    for (int j = 0; j < 8; j++)
    {
      if (digitalRead(pinsRX[j]) == LOW)
      {
        if (i != j)
          isStraight = false;
        if ((i == 0 && j != 2) || (i == 1 && j != 3) || (i == 2 && j != 0) || (i == 3 && j != 1) ||
            (i >= 4 && i != j))
          isCrossed = false;
      }
    }

    digitalWrite(pinsTX[i], HIGH);
    delay(10);
  }

  // Afficher le résultat
  if (isStraight)
  {
    Serial.println("Le câble est droit");
  }
  else if (isCrossed)
  {
    Serial.println("Le câble est croisé");
  }
  else
  {
    Serial.println("Câble non reconnu ou défectueux");
  }

  delay(2000); // Attendre 2 secondes avant le prochain test
}

// // Pins pour envoyer le signal (émetteur)
// const int outputPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

// // Pins pour recevoir le signal (récepteur)
// const int inputPins[8] = {A0, A1, A2, A3, A4, A5, 10, 11};

// // Tableau pour stocker les correspondances détectées
// int connections[8] = {-1, -1, -1, -1, -1, -1, -1, -1}; // -1 signifie non connecté

// void setup()
// {
//   // Configurer les pins de sortie
//   for (int i = 0; i < 8; i++)
//   {
//     pinMode(outputPins[i], OUTPUT);
//     digitalWrite(outputPins[i], LOW);
//   }

//   // Configurer les pins d'entrée
//   for (int i = 0; i < 8; i++)
//   {
//     pinMode(inputPins[i], INPUT);
//   }

//   // Démarrer la communication série
//   Serial.begin(9600);
//   Serial.println("Testeur de câble RJ45 démarré");
// }

// void testCable()
// {
//   // Réinitialiser les correspondances
//   for (int i = 0; i < 8; i++)
//   {
//     connections[i] = -1;
//   }

//   // Tester chaque fil
//   for (int i = 0; i < 8; i++)
//   {
//     digitalWrite(outputPins[i], HIGH); // Activer une sortie
//     delay(10);                         // Petit délai pour stabiliser

//     // Vérifier toutes les entrées
//     for (int j = 0; j < 8; j++)
//     {
//       if (digitalRead(inputPins[j]) == HIGH)
//       {
//         connections[i] = j; // Stocker la correspondance
//         break;              // Sortir dès qu'une connexion est trouvée
//       }
//     }

//     digitalWrite(outputPins[i], LOW); // Désactiver la sortie
//     delay(10);
//   }

//   // Analyser le résultat
//   analyzeCable();
// }

// void analyzeCable()
// {
//   Serial.println("\nRésultat du test :");

//   // Vérifier si tous les fils sont connectés
//   bool allConnected = true;
//   for (int i = 0; i < 8; i++)
//   {
//     if (connections[i] == -1)
//     {
//       allConnected = false;
//       Serial.print("Fil ");
//       Serial.print(i + 1);
//       Serial.println(" : non connecté (coupé)");
//     }
//     else
//     {
//       Serial.print("Fil ");
//       Serial.print(i + 1);
//       Serial.print(" -> Entrée ");
//       Serial.println(connections[i] + 1);
//     }
//   }

//   if (!allConnected)
//   {
//     Serial.println("Câble défectueux : au moins un fil est coupé.");
//     return;
//   }

//   // Vérifier si le câble est droit (straight)
//   bool isStraight = true;
//   for (int i = 0; i < 8; i++)
//   {
//     if (connections[i] != i)
//     {
//       isStraight = false;
//       break;
//     }
//   }

//   if (isStraight)
//   {
//     Serial.println("Câble droit (straight) détecté.");
//     return;
//   }

//   // Vérifier si le câble est croisé (crossover T568A/T568B classique)
//   bool isCrossover = (connections[0] == 2 && connections[1] == 5 &&
//                       connections[2] == 0 && connections[5] == 1 &&
//                       connections[3] == 3 && connections[4] == 4 &&
//                       connections[6] == 6 && connections[7] == 7);

//   if (isCrossover)
//   {
//     Serial.println("Câble croisé (crossover T568A/T568B) détecté.");
//   }
//   else
//   {
//     Serial.println("Câble ni droit ni croisé standard : configuration personnalisée ou erreur.");
//   }
// }

// void loop()
// {
//   Serial.println("\nNouveau test...");
//   testCable();
//   delay(5000); // Attendre 5 secondes avant de relancer le test
// }