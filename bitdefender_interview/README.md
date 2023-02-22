# Bitdefender - Ip Service

### Instalare

Am inclus un `Dockerfile` si un `docker-compose.yml`, asadar pentru instalare
de dependinte, setup, rulare se ruleaza doar comanda `docker-compose up --build` 
(sau cu `-d` daca vrem fara loguri).

**Setup-ul dureaza aproximativ un minut**, timp in care se insereaza in mongo toate 
datele necesare. Va rog sa asteptati pana cand api-ul porneste (se vede in loguri
pentru varianta fara `-d`, sau se poate verifica cu un request GET in browser pe 
`localhost:8080` care va da **Not Found** in momentul in care api-ul a pornit)

### Documentatie

#### Tehnologii

* `Python` 
* `Flask` 
* `MongoDB`
* `Docker` & `DockerCompose`
* `Bash` & `Unix` tools

#### Setup

Aceasta a fost etapa cea mai longeviva, intrucat nu am experienta extensiva
folosind docker. Am pierdut ore in sir incercand sa rulez proiectul folosind
de montarea unui volum local in instanta docker. Pana la urma am renuntat si
am ajuns la implementarea actuala in care pur si simplu se copiaza continutul
directorului de lucru in container si se continua de acolo.

Am folosit doua containere, unul pe care ruleaza API-ul si altul pentru baza
de date `MongoDB`.
</br>
</br>
</br>
</br>
#### Ip Ranges

M-am informat in legatura cu aceste ip-ranges si am gasite fisiere `json`
sugestive cu datele necesare de la fiecare dintre provideri. M-am concentrat
doar pe ipv4. 

Am scris cateva scripturi pentru a parsa fisierele, a extrage datele necesare
si a le introduce in baza de date intr-un format utilizabil. Ideea de baza, e
ca pot descrie un ip range `xxx.xxx.xxx.xxx/xx` ca pe o pereche de intregi,
transformand cea mai mica adresa si, respectiv cea mai mare, in intregi. Retin
pentru toata adresele disponibile in baza data cate un entry pentru
`lower_bound, upper_bound, provider` si astfel, daca vreau sa cataloghez un ip
random, ma uit in db daca existra vreun range in care se incadreaza.

Am folosit urmatoarele scripturi:
* `parse.py` -> citeste o lista de ip-uri in format clasic si le transforma
* intr-o lista de perechi (lower_bound, upper_bound) `update_ranges.py` ->
* citeste fisierele parsate cu scriptul anterior si actualizeaza baza de date
* `update_ranges.sh` -> descarca fisierele `json` pentru fiecare provider,
* apeleaza primul script pentru a le parsa, ruleaza al doilea script pentru a
* actualiza baza de date si in final curata fisierele extra

#### API

Api-ul este destul de simplut. Am folosit `python` si `flask` impreuna cu
`pymongo` pentru conexiunea la db. Am 4 endpoint-uri conforme cu descrierea.
Se poate testa superficial si rapid ruland `cat req | bash` din radacina
proiectului (req contine cateva requesturi hardcodate).

#### Problema cu request-ul de PUT

Din ce am inteles eu, request-ul de actualizare ar trebui sa actualizeze
provider-ul in cazul in care acesta se modifica in realitate (Amazon face
schimb cu Google sau ceva). Acest fapt era o problema deoarece eu initial
preluam datele o singura data la creare containerului din niste fisiere
descarcate in prealabil.

Ideea de rezolvare a fost crearea unui cronjob care ruleaza o data pe zi (am
inteles ca ip-range-urile se actualizeaza cam la o saptamana) care descarca
fisierele si reia operatiile de initializare (parsare, actualizare db).

Rezolvarea se vede in `src/scripts/entrypoint.sh` care se apeleaza la crearea
containerului. Acolo ma asigur ca se creeaza un entry in crontab-ul din
container.


#### Chestii ~~Chestie~~ extra

* verfic daca ip-ul este formatat corect cu ajutorul unei expresii regex am
* folosit si git ca sa se vada cat de cat progresul
