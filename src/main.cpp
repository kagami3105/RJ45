/*
  Titre      : Faire un programme qui va pouvoir déterminer si cable est droit ou croisé
  Auteur     : Boladji ODELOUI
  Date       : 25/02/2025
  Description: Testeur RJ45
  Version    : 0.0.1
*/


#include <Arduino.h>
// #include <ArduinoUnit.h>

class TesteurCable
{
protected:
    const int *broches;
    int brocheCount;

public:
    TesteurCable(const int *_broches, int _brocheCount) : broches(_broches), brocheCount(_brocheCount) {}
    virtual void setup() = 0;
    virtual void loop() = 0;
};

class Emetteur : public TesteurCable
{
public:
    Emetteur(const int *_broches, int _brocheCount) : TesteurCable(_broches, _brocheCount) {}
    void setup() override
    {
        for (int i = 0; i < brocheCount; i++)
        {
            pinMode(broches[i], OUTPUT);
        }
    }
    void loop() override
    {
        for (int i = 0; i < brocheCount; i++)
        {
            digitalWrite(broches[i], HIGH);
            delay(10);
            digitalWrite(broches[i], LOW);
        }
        delay(500);
    }
};

class Recepteur : public TesteurCable
{
public:
    Recepteur(const int *_broches, int _brocheCount) : TesteurCable(_broches, _brocheCount) {}
    void setup() override
    {
        for (int i = 0; i < brocheCount; i++)
        {
            pinMode(broches[i], INPUT);
        }
    }

    String DetecteurCable()
    {
        int tab[8];
        for (int i = 0; i < brocheCount; i++)
        {
            tab[i] = digitalRead(broches[i]);
        }
        bool type1 = true;
        bool type2 = true;

        for (int i = 0; i < brocheCount; i++)
        {
            if (tab[i] != HIGH)
                type1 = false;
            if (tab[brocheCount - 1 - i] != HIGH)
                type2 = false;
        }
        if (type1)
            return ("Câble droit");
        if (type2)
            return ("Câble croisé");
        return ("Câble non détecté");
    }
    void loop() override
    {
        Serial.print("Câble détecté : ");
        Serial.println(DetecteurCable());
        delay(500);
    }
};

const int testBroches[8] = {2, 3, 4, 5, 6, 7, 8, 9};
Emetteur emetteur(testBroches, 8);
Recepteur recepteur(testBroches, 8);

void setup()
{
    Serial.begin(9600);
    emetteur.setup();
    recepteur.setup();
    // Test::run();
}

void loop()
{
    emetteur.loop();
    recepteur.loop();
}

// test(detectionCableType_Droit)
// {
//     int array[8] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
//     for (int i = 0; i < 8; i++)
//     {
//         digitalWrite(testBroches[i], array[i]);
//     }
//     assertEqual(recepteur.DetecteurCable(), "Câble droit");
// }

// test(detectionCableType_Croise)
// {
//     int array[8] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
//     for (int i = 0; i < 8; i++)
//     {
//         digitalWrite(testBroches[7 - i], array[i]);
//     }
//     assertEqual(recepteur.DetecteurCable(), "Câble croisé");
// }

// test(test_detectionCableType_None)
// {
//     int array[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
//     for (int i = 0; i < 8; i++)
//     {
//         digitalWrite(testBroches[i], array[i]);
//     }
//     assertEqual(recepteur.DetecteurCable(), "Câble non détecté");
// }