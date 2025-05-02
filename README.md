# Continente
Proiect 2
Scopul proiectului
Sa modeleze lumea geografica la nivel de continente si tari, oferind statistici demografice, economice si de calitate a vietii, plus mecanisme de extindere (pattern‑uri, exceptii, serializare).

Functionalitati implementate
Statistici agregate
Populatie, suprafata, densitate, GDP total, scor mediu Quality‑of‑Life.

Top‑N
top_by_gdp(n) si top_by_qol(n) returneaza cele mai bogate / cele mai „fericite” tari.

Validare stricta a datelor
Populatie > 0, suprafata > 0, GDP ≥ 0, indici QoL ∈ [0,10]; altfel InvalidCountryData.

Adaugare / stergere de tari
Actualizeaza automat statisticile si declanseaza notificari Observer.

Observer pattern
Poti atasa oricate log‑gere; mesajele apar fara sa modifici codul de business.

Management corect al resurselor
unique_ptr, weak_ptr, copy‑and‑swap, constructor virtual pentru copiere polimorfa.

Dynamic‑cast cu sens
Demonstreaza downcast valid la derivate (ex. identifici rapid daca un continent este Europe).

Atribute / functii statice
Contor global de continente create, statistici globale (extensibil).

Interfete de nivel inalt
describe(), overview(), serializare — evita getters triviali.

Demonstreaza toate cerintele laboratorului: mostenire, functii virtuale, pointeri la baza, smart‑pointers, exceptii tematice, STL, const‑corectitudine, pattern‑uri.

Codul este organizat clar pe fisiere .hpp / .cpp, fara using namespace std, usor de extins sau testat.
