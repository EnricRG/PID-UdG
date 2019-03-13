#include "Window.h"
#include "RGBColor.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

const int NUM_VOCALS = 5;
const int NUM_LLETRES = 26;
const int NUM_COLORS = 7;
const float VOLTA_COMPLETA = 360;
const RGBColor COLORS[NUM_COLORS] = { RED, MAGENTA, BLUE, CIAN, GREEN, YELLOW, BLACK };
const char VOCALS[NUM_VOCALS] = { 'A','E','I','O','U' };

bool esMajuscula(char c) {
	return (c >= 'A' && c <= 'Z');
}

bool esMinuscula(char c) {
	return (c >= 'a' && c <= 'z');
}

char aMinuscula(char c) {
	if (esMajuscula(c)) return c + 32;
	else return c;
}

bool esVocal(char c) {
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

int indexVocal(char c) {
	if (!esVocal(c)) return -1;
	else {
		char caux = aMinuscula(c);
		int index;
		switch (c) {
		case 'a':
			index = 1;
			break;
		case 'e':
			index = 2;
			break;
		case 'i':
			index = 3;
			break;
		case 'o':
			index = 4;
			break;
		case 'u':
			index = 5;
			break;
		default:
			index = 0;
			break;
		}

		return index;
	}
}

int indexLletraAbecedari(char c) {
	if (esMinuscula(c)) return c - 96;
	else return -1;
}

char lletraAbecedari(int index) {
	if (index > 0 && index <= NUM_LLETRES) return index + 96;
	else return 0;
}


void dibuixarGraficPastis(const int * taula_recompte, int mida_taula_recompte) {
	int ample = 500, alt = 500;
	std::string titol_finestra = "Grafic de pastis";

	Window w(titol_finestra, ample, alt); //4th parameter is the drawing color
	w.t_penUp(); //usarem les tortugues per dibuixar text, no linies, i per tant aixequem el pinzell

	int acumulat_total = taula_recompte[0];
	
	float angle_inicial = 0, angle_del_tall;
	float radi = 150;
	for (int i = 1; i < mida_taula_recompte; i++) {
		if (taula_recompte[i] != 0) {
			float percentatge = taula_recompte[i] / (1.0*acumulat_total);
			angle_del_tall = percentatge * VOLTA_COMPLETA;

			//// Aixo no es gens necessari, pero queda millor: calcular els punts on s'escriu cada lletra del grafic (amb tortugues es molt facil) ////
			
			w.t_setPos(ample / 2, alt / 2);
			w.t_setHeading((angle_inicial + (angle_del_tall / 2)));
			w.t_forward(radi + 20);

			stringstream percentatge_text_stream;

			if (w.t_heading() >= 90 && w.t_heading() <= 270) { //nomes valid si es fa en graus
				percentatge_text_stream << " (" << taula_recompte[i] << ") " << fixed << setprecision(2) << percentatge * 100 << "%" << "   " << VOCALS[i-1];
				w.t_label(percentatge_text_stream.str(), TEXT_ALIGN_RIGHT);
			}
			else {
				percentatge_text_stream << VOCALS[i-1] << "   " << fixed << setprecision(2) << percentatge * 100 << "%" << " (" << taula_recompte[i] << ") ";
				w.t_label(percentatge_text_stream.str(), TEXT_ALIGN_LEFT);
			}
			////				fi del tall de codi estetic					////

			w.filled_pieslice(ample / 2, alt / 2, radi, angle_inicial, angle_del_tall, COLORS[i-1]); //l'alumne no usa la estructura proporcionada per la llibreria, -1 punt
			angle_inicial += angle_del_tall;
		}
	}

	w.waitAnyKeypress();
}

void comptarVocalsFitxer() {

	int comptador_vocals[NUM_VOCALS+1]; //deixem una posició extra per el recompte total
	for (int i = 0; i < NUM_VOCALS+1; i++) comptador_vocals[i] = 0; //inicialitzem tots els valors de l'array
	
	string nom_fitxer;

	cout << "Introdueix el nom del fitxer (recorda que ha d'estar al directori on execuits aquest programa): " << endl;
	cin >> nom_fitxer; //no admet espais en el nom de fitxer, getline() si es volgues aquesta opcio

	fstream fitxer; 
	fitxer.open(nom_fitxer.c_str()); //escapem els caracters especials amb \\ 

	if (!fitxer.is_open()) cout << "No s'ha pogut obrir el fitxer " << nom_fitxer << endl;
	else {
		char caracter;
		fitxer.get(caracter);
		while (!fitxer.eof()) {
			if (esVocal(caracter)) {
				comptador_vocals[0]++; //incrementem el comptador global
				comptador_vocals[ indexVocal(aMinuscula(caracter)) ]++; //incrementem el comptador de la vocal en concret
			}
			fitxer.get(caracter);
		}
		fitxer.close();

		dibuixarGraficPastis(comptador_vocals, NUM_VOCALS + 1);
	}
}

void dibuixarHistograma(Window & w, int ample, int alt, const int * taula_recompte, const int * colors, int mida_taula_recompte) {
	
	int acumulat_total = taula_recompte[0];
	float espai_entre_rectangles = 2;
	float pixels_reservats_per_a_rectangles = alt - (mida_taula_recompte - 1) * espai_entre_rectangles;
	float alt_rectangle = pixels_reservats_per_a_rectangles / NUM_LLETRES;

	for (int i = 1; i < mida_taula_recompte; i++) {
		int index_lletra = NUM_LLETRES - i + 1;
		float longitud_rectangle = ((double)taula_recompte[index_lletra]/acumulat_total) * ample;

		//cout << taula_recompte[index_lletra] << " " << acumulat_total << endl;

		Point2D p1(0, i*alt_rectangle + (i-1) * espai_entre_rectangles);
		Point2D p2(longitud_rectangle, p1.y - alt_rectangle);
		w.filled_rectangle(p1,p2,COLORS[colors[i]]);

		Point2D posicio_lletra(10, p1.y);
		char lletra = lletraAbecedari(index_lletra);
		string lletra_str(1,lletra); //construir una string a partir d'un caracter pots usar string(1,char)
		stringstream text;
		text << lletra << "  " << taula_recompte[index_lletra];

		w.text(posicio_lletra, text.str(), TEXT_ALIGN_CENTER);
	}
}

void comptarLletresInteractiu() {
	cin.ignore(1, '\n');

	int comptador_lletres[NUM_LLETRES+1];
	int colors_lletres[NUM_LLETRES+1]; //+1 per evitar tenir que fer conversions d'index, perdem un espai a canvi de simplicitat en el codi
	srand(time(NULL));
	comptador_lletres[0] = 0; //per evitar ficar condicions dins de la iteracio
	for (int i = 1; i < NUM_LLETRES + 1; i++) {
		comptador_lletres[i] = 0;
		colors_lletres[i] = rand() % (NUM_COLORS-1); //-1 perque no volem que ens surti el color negre
	}

	int ample = 500, alt = 700;
	std::string titol_finestra = "Histograma";

	Window w(titol_finestra, ample, alt); //4th parameter is the drawing color

	cout << "Tu ves entrant caracters que jo tels conto..." << endl;
	char caracter = cin.get();
	while (caracter != '#') {
		char caracter_auxiliar = aMinuscula(caracter);
		if (esMinuscula(caracter_auxiliar)) { //comprovem que sigui efectivament una lletra
			comptador_lletres[0]++;
			comptador_lletres[ indexLletraAbecedari(caracter_auxiliar) ]++;
		}

		if (caracter == '\n') {
			w.clear();
			dibuixarHistograma(w, ample, alt, comptador_lletres, colors_lletres, NUM_LLETRES + 1);
		}

		caracter = cin.get();
	}

	cin.ignore(1000,'\n'); //netejem el buffer per si haugues quedat algun caracter abans del salt de linia
}

int rebreInputDelTeclatCASE(Window & w) {
	int tecla_apretada, nombre_retorn;

	tecla_apretada = w.waitAnyKeypress();

	switch (tecla_apretada) {
		case KEYBOARD_KEY_DELETE:		//like KEYBOARD_KEY_DELETE || KEYBOARD_KEY_BACKSPACE
		case KEYBOARD_KEY_BACKSPACE:
			nombre_retorn = -1;
			break;
		case KEYBOARD_KEY_ESCAPE:
			nombre_retorn = 0;
			break;
		case KEYBOARD_KEY_RIGHT:
			nombre_retorn = 1;
			break;
		case KEYBOARD_KEY_UP:
			nombre_retorn = 2;
			break;
		case KEYBOARD_KEY_LEFT:
			nombre_retorn = 3;
			break;
		case KEYBOARD_KEY_DOWN:
			nombre_retorn = 4;
			break;
		case KEYBOARD_KEY_SPACE:
			nombre_retorn = 5;
			break;
		default:
			nombre_retorn = -2;
			break;
	}

	return nombre_retorn;
}

int rebreInputDelTeclatIF(Window & w) {
	int tecla_apretada, nombre_retorn;

	tecla_apretada = w.waitAnyKeypress();

	if (tecla_apretada == KEYBOARD_KEY_DELETE || tecla_apretada == KEYBOARD_KEY_BACKSPACE)
		nombre_retorn = -1;
	else if (tecla_apretada == KEYBOARD_KEY_ESCAPE)
		nombre_retorn = 0;
	else if (tecla_apretada == KEYBOARD_KEY_RIGHT)
		nombre_retorn = 1;
	else if (tecla_apretada == KEYBOARD_KEY_UP)
		nombre_retorn = 2;
	else if (tecla_apretada == KEYBOARD_KEY_LEFT)
		nombre_retorn = 3;
	else if (tecla_apretada == KEYBOARD_KEY_DOWN)
		nombre_retorn = 4;
	else if (tecla_apretada == KEYBOARD_KEY_SPACE)
		nombre_retorn = 5;
	else
		nombre_retorn = -2;

	return nombre_retorn;
}

void moureTortuga() {
	int ample= 800, alt=600;
	Window finestra("Tortugueta", ample, alt, WHITE, GREEN);	//Declarem la finestra amb titol "Tortugueta", amplada 'ample' i alçada 'alt', i color de fons negre i color de dibuix verd

	//Preparem a la tortuga
	finestra.t_setPos(ample / 2, alt / 2);						//La coloquem al centre de la pantalla
	finestra.t_show();											//fem visible el cursor de la tortuga

	finestra.update();											//Opcional, refresquem la pantalla per a que es vegi el fons i el cursor des del principi

	int distancia_salt_tortuga = 25;							//Distància que recorrerà la tortuga en cada iteració
	int seleccio_usuari;

	seleccio_usuari = rebreInputDelTeclatCASE(finestra);

	while (seleccio_usuari != 0) {

		if (seleccio_usuari != -2) {								//només volem actuar si coneixem la tecla que ens han entrat
			
			if (seleccio_usuari == 1) {								//si l'usuari apreta la tecla RIGHT
				finestra.t_setHeading(0);							//posicionem la tortuga mirant cap a la dreta (0 graus absoluts)
			}
			else if (seleccio_usuari == 2) {						//si l'usuari apreta la tecla UP
				finestra.t_setHeading(90);							//posicionem la tortuga mirant cap amunt (90 graus absoluts)
			}
			else if (seleccio_usuari == 3) {						//si l'usuari apreta la tecla LEFT
				finestra.t_setHeading(180);							//posicionem la tortuga mirant cap a l'esquerra (180 graus absoluts)
			}
			else if (seleccio_usuari == 4) {						//si l'usuari apreta la tecla DOWN
				finestra.t_setHeading(270);							//posicionem la tortuga mirant cap avall (270 graus absoluts)
			}
			else if (seleccio_usuari == 5) {
				finestra.t_swapPen();
			}
			else if (seleccio_usuari == -1) {
				finestra.clear();									//Netejem la finestra
				finestra.t_setPos(ample / 2, alt / 2);				//recoloquem la tortuga al centre de la pantalla
			}

			if (seleccio_usuari > 0 && seleccio_usuari < 5) finestra.t_forward(distancia_salt_tortuga);	//fem avançar la tortuga (no ho fem si s'acaba de netejar la pantalla)
		}

		seleccio_usuari = rebreInputDelTeclatCASE(finestra);
	}
}

void mostrarMenu() {
	cout << endl << endl;
	cout << "2. Decisions i iteracions: Moure la tortuga per la pantalla" << endl;
	cout << "5. Tractament de sequencies: Comptar vocals d'un fitxer donat" << endl;
	cout << "6. Tractament de sequencies: Comptar lletres des de l'entrada estandard" << endl;
	cout << "0. Sortir" << endl << endl;
}

void menuDecisions() {
	cout << "(1) Triar el color de fons de la finestra." << endl;
	cout << "(2) Dibuixar figures en funcio de l'entrada." << endl;

	cout << "(0) Sortir." << endl;
}

void triarColorFons() {
	cout << "Tria un color:" << endl;
	cout << "(y) groc" << endl;
	cout << "(b) blau" << endl;
	cout << "(g) verd" << endl;
	cout << "(r) vermell" << endl;
	cout << endl << "Si no tries cap d'aquestes opcions, el fons sera negre" << endl;

	char input;
	cin >> input;
	
	RGBColor color;
	if (input == 'y') color = YELLOW;
	else if (input == 'b') color = BLUE;
	else if (input == 'g') color = GREEN;
	else if (input == 'r') color = RED;
	else color = BLACK;

	Window finestra(400, 400, color);	//creem una finestra 400x400 amb el fons del color escollit
	finestra.update();
	finestra.rest(5);	//deixem la finstra oberta 5 segons.
}

void triarFigures() {

}

void decisions() {
	cout << "Quines decisions vols prendre?";
	menuDecisions();
	
	int seleccio;
	cin >> seleccio;

	while (seleccio != 0) {

		switch (seleccio) {
			case 0: break; //no fem res i marxem
			case 1:
				triarColorFons();
				break;
			case 2:
				triarFigures();
				break;
			default:
				cout << "No has decidit be. Aquesta opcio no existeix." << endl;
				break;
		}

		cin >> seleccio;
	}
}

int main1(int argc, char **argv) {
	int seleccio;
	
	cout << "Que vols fer?";
	mostrarMenu();
	cout << "Seleccio: ";
	cin >> seleccio;

	while (seleccio != 0) {
		switch (seleccio) {
		case 0: break; //no fem res i marxem
		case 1: 
			decisions();
			break;
		case 2:
			moureTortuga();
			break;
		case 5:
			comptarVocalsFitxer();
			break;
		case 6: 
			comptarLletresInteractiu();
			break;
		default:
			cout << "Ho sento, m'he equivocat d'opcio. Ah no, que has estat tu!" << endl;
			break;
		}

		cout << "Vols fer alguna cosa mes?";
		mostrarMenu();
		cout << "Seleccio: ";
		cin >> seleccio;
	}

	cout << "Fins aviat!" << endl;
	
	return 0;
}