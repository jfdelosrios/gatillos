#include "stdafx.h"
#include "IndicatorInterfaceUnit.h"


int periodoMedia = 200;
int Shift = 0;
int MAtype = 0;
int ApplyToPrice = 0;
int VShift = 0;

int distanciaMedia1 = 94;
double fraccionPenetrando = 0.413751;
bool mostrarGatillos = true;

/*
int distanciaInflexionGatillo = 24;
int maximaExtensionMediaX = 382;
int maximaExtensionMediaY = 4211;

const int tamanoCaja = 25;

bool mostrarExterna = true;
double relacionCuerpoRangoEnvolvente = 0.32;
double fraccionCuerpoNoEnvolvento = 0.042554;
double fraccionMechaNoEnvolventa = 0.07;
double relacionEnvueltaEnvolvente = 0.94;

bool mostrarInterna = true;
double proporcionCuerpoGrandeInterna = 0.409774;
double mechaSalienteInterna = 0.165563;
double relacionCuerpoInternaCuerpoGrande = 0.454707;

bool mostrarClimax = true;
*/
TIndexBuffer climaxSube;
TIndexBuffer climaxBaja;

TIndexBuffer internaSube;
TIndexBuffer internaBaja;
TIndexBuffer internaCuerpoSube;
TIndexBuffer internaCuerpoBaja;

TIndexBuffer externaSube;
TIndexBuffer externaBaja;
TIndexBuffer externaCuerpoSube;
TIndexBuffer externaCuerpoBaja;

TIndexBuffer MA;

TIndexBuffer velaImperante;
const double valorVelaImperante = 0.05;

TIndexBuffer SMA;

EXPORT void __stdcall Init()
{
	IndicatorShortName("Gatillos");
	SetOutputWindow(ow_ChartWindow);
	SetEmptyValue(0);

	AddSeparator("Media");
	RegOption("periodoMedia", ot_Integer, &periodoMedia);
	SetOptionRange("periodoMedia", 1, INT_MAX);
	RegOption("HShift", ot_Integer, &Shift);
	RegOption("VShift", ot_Integer, &VShift);
	RegMATypeOption(&MAtype);
	RegApplyToPriceOption(&ApplyToPrice);

	AddSeparator("relacion media-gatillo");
	RegOption("mostrarGatillos", ot_Boolean, &mostrarGatillos);
	RegOption("distanciaMedia", ot_Integer, &distanciaMedia1);
	SetOptionRange("distanciaMedia", 0, INT_MAX);
	RegOption("fraccionPenetrando", ot_Double, &fraccionPenetrando);
	SetOptionDigits("fraccionPenetrando", 6);
	SetOptionRange("fraccionPenetrando", 0, DBL_MAX);

	/*
	int periodoMedia = 200;
	int hshift = 0;
	int vshift = 0;
	int MAtype = 0;
	int MA_applyPrice = 0;
	int distanciaMedia1 = 94;
	double fraccionPenetrando = 0.413751;
	*/

	//RegOption("distanciaInflexionGatillo", ot_Integer, &distanciaInflexionGatillo);

	//RegOption("maximaExtensionMediaX", ot_Integer, &maximaExtensionMediaX);
	//RegOption("maximaExtensionMediaY", ot_Integer, &maximaExtensionMediaY);

	//AddSeparator("Externa");
	//RegOption("mostrarExterna", ot_Boolean, &mostrarExterna);
	//RegOption("relacionCuerpoRangoEnvolvente", ot_Double, &relacionCuerpoRangoEnvolvente);
	//SetOptionDigits("relacionCuerpoRangoEnvolvente", 6);

	//RegOption("fraccionCuerpoNoEnvolvento", ot_Double, &fraccionCuerpoNoEnvolvento);
	//SetOptionDigits("fraccionCuerpoNoEnvolvento", 6);

	//RegOption("fraccionMechaNoEnvolventa", ot_Double, &fraccionMechaNoEnvolventa);
	//SetOptionDigits("fraccionMechaNoEnvolventa", 6);

	//RegOption("relacion Envuelta/aEnvolvente", ot_Double, &relacionEnvueltaEnvolvente);
	//SetOptionDigits("relacion Envuelta/aEnvolvente", 6);

	//AddSeparator("Interna");
	//RegOption("proporcionCuerpoGrandeInterna", ot_Double, &proporcionCuerpoGrandeInterna);
	//SetOptionDigits("proporcionCuerpoGrandeInterna", 6);

	//RegOption("mostrarInterna", ot_Boolean, &mostrarInterna);
	//RegOption("mechaSalienteInterna", ot_Double, &mechaSalienteInterna);
	//SetOptionDigits("mechaSalienteInterna", 6);

	//RegOption("Relacion CuerpoInterna/CuerpoGrande", ot_Double, &relacionCuerpoInternaCuerpoGrande);
	//SetOptionDigits("Relacion CuerpoInterna/CuerpoGrande", 6);

	//AddSeparator("Climax");
	//RegOption("mostrarClimax", ot_Boolean, &mostrarClimax);

	IndicatorBuffers(12);
	// create buffers
	/*
	UpBuff = CreateIndexBuffer();
	DownBuff = CreateIndexBuffer();
	SetIndexBuffer(0, UpBuff);
	SetIndexStyle(0, ds_Symbol, psSolid, 1, clGreen);
	SetIndexSymbol(0, 158, 0, -10);
	SetIndexLabel(0, "Fractal Up");
	SetIndexBuffer(1, DownBuff);
	SetIndexStyle(1, ds_Symbol, psSolid, 1, clRed);
	SetIndexSymbol(1, 158, 0, 10);
	SetIndexLabel(1, "Fractal Down");
	*/

	internaCuerpoBaja = CreateIndexBuffer();
	SetIndexBuffer(0, internaCuerpoBaja);
	SetIndexLabel(0, "internaCuerpoBaja");
	//SetIndexStyle(0, ds_Histogram, psSolid, 1, 0x4747E7);
	SetIndexStyle(0, ds_Symbol, psSolid, 1, 0x4747E7);
	SetIndexSymbol(0, 158, 0, 10);

	internaBaja = CreateIndexBuffer();
	SetIndexBuffer(1, internaBaja);
	SetIndexLabel(1, "internaBaja");
	//SetIndexStyle(1, ds_Histogram, psSolid, 1, clrRed);
	SetIndexStyle(1, ds_Symbol, psSolid, 1, clrRed);
	SetIndexSymbol(1, 158, 0, 10);

	internaCuerpoSube = CreateIndexBuffer();
	SetIndexBuffer(2, internaCuerpoSube);
	SetIndexLabel(2, "internaCuerpoSube");
	//SetIndexStyle(2, ds_Histogram, psSolid, 1, 0x47A747);
	SetIndexStyle(2, ds_Symbol, psSolid, 1, 0x47A747);
	SetIndexSymbol(2, 158, 0, -10);

	internaSube = CreateIndexBuffer();
	SetIndexBuffer(3, internaSube);
	SetIndexLabel(3, "internaSube");
	//SetIndexStyle(3, ds_Histogram, psSolid, 1, clrGreen);
	SetIndexStyle(3, ds_Symbol, psSolid, 1, clrGreen);
	SetIndexSymbol(3, 158, 0, -10);

	externaCuerpoBaja = CreateIndexBuffer();
	SetIndexBuffer(4, externaCuerpoBaja);
	SetIndexLabel(4, "externaCuerpoBaja");
	//SetIndexStyle(4, ds_Histogram, psSolid, 1, 0x4747E7);
	SetIndexStyle(4, ds_Symbol, psSolid, 1, 0x4747E7);
	SetIndexSymbol(4, 158, 0, 10);

	externaBaja = CreateIndexBuffer();
	SetIndexBuffer(5, externaBaja);
	SetIndexLabel(5, "externaBaja");
	//SetIndexStyle(5, ds_Histogram, psSolid, 1, clrRed);
	SetIndexStyle(5, ds_Symbol, psSolid, 1, clrRed);
	SetIndexSymbol(5, 158, 0, 10);

	externaCuerpoSube = CreateIndexBuffer();
	SetIndexBuffer(6, externaCuerpoSube);
	SetIndexLabel(6, "externaCuerpoSube");
	//SetIndexStyle(6, ds_Histogram, psSolid, 1, 0x47A747);
	SetIndexStyle(6, ds_Symbol, psSolid, 1, 0x47A747);
	SetIndexSymbol(6, 158, 0, -10);

	externaSube = CreateIndexBuffer();
	SetIndexBuffer(7, externaSube);
	SetIndexLabel(7, "externaSube");
	//SetIndexStyle(7, ds_Histogram, psSolid, 1, clrGreen);
	SetIndexStyle(7, ds_Symbol, psSolid, 1, clrGreen);
	SetIndexSymbol(7, 158, 0, -10);

	climaxBaja = CreateIndexBuffer();
	SetIndexBuffer(8, climaxBaja);
	SetIndexLabel(8, "climaxBaja");
	//SetIndexStyle(8, ds_Histogram, psSolid, 1, clrRed);
	SetIndexStyle(8, ds_Symbol, psSolid, 1, clrRed);
	SetIndexSymbol(8, 158, 0, 10);

	climaxSube = CreateIndexBuffer();
	SetIndexBuffer(9, climaxSube);
	SetIndexLabel(9, "climaxSube");
	//SetIndexStyle(9, ds_Histogram, psSolid, 1, clrGreen);
	SetIndexStyle(9, ds_Symbol, psSolid, 1, clrGreen);
	SetIndexSymbol(9, 158, 0, -10);

	velaImperante = CreateIndexBuffer();
	SetIndexBuffer(10, velaImperante);
	SetIndexLabel(10, "velaImperante");
	SetIndexStyle(10, ds_Histogram, psSolid, 1, clr_Transparent);

	MA = CreateIndexBuffer();
	SetIndexBuffer(11, MA);
	SetIndexLabel(11, "MA");
	SetIndexStyle(11, ds_Line, psSolid, 2, clrBlue);

	SMA = CreateIndexBuffer();
};

EXPORT void __stdcall Done()
{
}

EXPORT void __stdcall OnParamsChange()
{
	SetBufferShift(1, Shift);
};



/*
bool EvaluarMaximoLocal(const int index)
{
	int i;

	for (i = (index + 1); i >= index; i--)
		if (MA[i + 1] < MA[i])
			return false;

	for (i = index; i <= Bars(); i++)
	{
		if (i == Bars())
			return false;

		if (MA[i + 1] == 0)
			return false;

		if (MA[i + 1] < MA[i])
			break;
	}

	for (i = i; i <= Bars(); i++)
	{
		if (i == Bars())
			return false;

		if (MA[i + 1] == 0)
			return false;

		if (max(Close(i + 1), Open(i + 1)) > MA[i + 1])
			break;
	}

	for (i = i; i >= 0; i--)
	{
		if (i == 0)
			return false;

		if (MA[i] > MA[i - 1])
			break;
	}

	if ((i - index) < distanciaInflexionGatillo)
		return false;
	/*
	if ((i - index) > maximaExtensionMediaX)
		return false;

	if ((MA[i] - MA[index]) > (maximaExtensionMediaY*Point()))
		return false;
	//
	return true;
}
*//*
bool EvaluarMinimoLocal(const int index)
{
	int i;

	for (i = (index + 1); i >= index; i--)
		if (MA[i + 1] > MA[i])
			return false;

	for (i = index; i <= Bars(); i++)
	{
		if (i == Bars())
			return false;

		if (MA[i + 1] == 0)
			return false;

		if (MA[i + 1] > MA[i])
			break;
	}

	for (i = i; i <= Bars(); i++)
	{
		if (i == Bars())
			return false;

		if (MA[i + 1] == 0)
			return false;

		if (min(Close(i + 1), Open(i + 1)) < MA[i + 1])
			break;
	}

	for (i = i; i >= 0; i--)
	{
		if (i == 0)
			return false;

		if (MA[i] < MA[i - 1])
			break;
	}

	if ((i - index) < distanciaInflexionGatillo)
		return false;
	/*
	if ((i - index) > maximaExtensionMediaX)
		return false;

	if ((MA[index] - MA[i]) > (maximaExtensionMediaY*Point()))
		return false;
	//
	return true;
}
*/
bool climaxArriba(const int index)
{
	if (velaImperante[index] == 0)
		return false;
	/*
	if ((index + 3) > (Bars() - 1))
		return false;
	*/
	if (index < 1)
		return false;

	/*
	//dia 5, 1:22:56
	if (Open(index) > Close(index))
		return false;
*/
/*
	//dia 5, 1:22:56
	if (!((Low(index - 1) < Open(index)) && (Close(index - 1) > High(index))))
		return false;
	*/

	if (Low(index) > (MA[index] + distanciaMedia1 * Point()))
		return false;

	if (min(Close(index), Open(index)) < (High(index) - (1 / 3.0)*(High(index) - Low(index))))
		return false;
	/*
	for (int cont = (index + 1); cont <= (index + 2); cont++)
		if (Low(index) >= Low(cont))
			return false;
	*/


	if ((Low(index) + fraccionPenetrando * (High(index) - Low(index))) < MA[index])
		return false;
	/*
	const double tamanoClimax = High(index) - Low(index);

	for (int cont = (index + 1); cont <= (index + 3); cont++)
		if (tamanoClimax < (High(cont) - Low(cont)))
			return false;
	*/
	/*
	if (!EvaluarMinimoLocal(index))
		return false;
	*/
	return true;
}

bool climaxAbajo(const int index)
{

	if (velaImperante[index] == 0)
		return false;

	/*
	//dia 5, 1:22:56
	if (Open(index) < Close(index))
		return false;
	*/
	/*
	//dia 5, 1:22:56
	if (!((High(index - 1) > Open(index)) && (Close(index - 1) < Low(index))))
		return false;
		*/

	if (max(Close(index), Open(index)) > ((High(index) - Low(index)) *(1 / 3.0) + Low(index)))
		return false;
	/*
	for (int cont = (index + 1); cont <= (index + 2); cont++)
		if (High(index) <= High(cont))
			return false;
	*/
	if (High(index) < (MA[index] - distanciaMedia1 * Point()))
		return false;


	if ((High(index) - fraccionPenetrando * (High(index) - Low(index))) > MA[index])
		return false;

	/*
	const double tamanoClimax = High(index) - Low(index);

	for (int cont = (index + 1); cont <= (index + 3); cont++)
		if (tamanoClimax < (High(cont) - Low(cont)))
			return false;
	*/
	/*
	if (!EvaluarMaximoLocal(index))
		return false;
	*/
	return true;
}

short int internaAbajo(const int index)
{
	if (velaImperante[index + 1] == 0)
		return 0;

	if (Close(index) >= Close(index + 1))
		return 0;

	const double cuerpoPequena = Open(index) - Close(index);

	if (cuerpoPequena < 0)
		return 0;

	const double cuerpoGrande = Close(index + 1) - Open(index + 1);

	if (cuerpoPequena >= cuerpoGrande)
		return 0;

	if (((Open(index + 1) + Close(index + 1)) * 0.5) > Close(index)) //por jf
		return 0;

	/*
	//video 6, 0:02:28
	if (((High(index + 1) + Low(index + 1)) *0.5) > Close(index))
		return 0;
	*/

	if (
		(Low(index) < (High(index + 1) - (2 / 3.0)*(High(index + 1) - Low(index + 1)))) //video 6, 0:03:58
		&&
		(Low(index) < (Close(index + 1) - (2 / 3.0)*(Open(index + 1) - Close(index + 1)))) //por jf
		)
		return 0;

	if (High(index + 1) < High(index))
		return 1;

	return 2;
}

short int internaArriba(const int index)
{
	if (velaImperante[index + 1] == 0)
		return 0;

	if (Close(index) <= Close(index + 1))
		return 0;

	const double cuerpoPequena = Close(index) - Open(index);

	if (cuerpoPequena < 0)
		return 0;

	const double cuerpoGrande = Open(index + 1) - Close(index + 1);

	if (cuerpoPequena >= cuerpoGrande)
		return 0;

	if (((Open(index + 1) + Close(index + 1)) * 0.5) < Close(index)) //por jf
		return 0;

	/*
	if (((High(index + 1) + Low(index + 1)) * 0.5) < Close(index)) //video 6, 0:02:28
		return 0;
		*/

	if (
		(High(index) > (Low(index + 1) + (2 / 3.0)*(High(index + 1) - Low(index + 1)))) //video 6, 0:03:58
		&&
		(High(index) > (Close(index + 1) + (2 / 3.0)*(Open(index + 1) - Close(index + 1)))) //por jf
		)
		return 0;

	if (Low(index + 1) > Low(index))
		return 1;

	return 2;
}

short int externaArriba(const int index)
{
	if (velaImperante[index] == 0)
		return 0;

	if (Open(index + 1) <= Open(index))
		return 0;

	const double cuerpoPequena = Open(index + 1) - Close(index + 1);

	if (cuerpoPequena < 0)
		return 0;

	const double cuerpoGrande = Close(index) - Open(index);

	if (cuerpoPequena >= cuerpoGrande)
		return 0;
	/*
	if (((Open(index) + Close(index)) * 0.499934) < Open(index + 1)) //por jf
		return 0;
	*/
	/*
	if (((High(index) + Low(index)) * 0.5) < Open(index + 1)) //video 6, 0:02:28
		return 0;
		*/
		/*
			if (
				(High(index + 1) > (Low(index) + 0.920455*(High(index) - Low(index)))) //video 6, 0:03:58
				)
				return 0;
			*/

	if (Open(index + 1) <= Open(index)) //por jf
		return 0;

	if ((Low(index + 1) <= Low(index)) || (High(index + 1) >= High(index))) //por jf
		return 1;

	return 2;
}

short int externaAbajo(const int index)
{
	if (velaImperante[index] == 0)
		return 0;

	if (Open(index + 1) >= Open(index))
		return 0;

	const double cuerpoPequena = Close(index + 1) - Open(index + 1);

	if (cuerpoPequena < 0)
		return 0;

	const double cuerpoGrande = Open(index) - Close(index);

	if (cuerpoPequena >= cuerpoGrande)
		return 0;
	/*
		if (((Open(index) + Close(index)) * 0.499934) > Open(index + 1)) //por jf
			return 0;



		if (((High(index) + Low(index)) * 0.5) > Open(index + 1)) //video 6, 0:02:28
			return 0;


			if (
				(Low(index + 1) < (High(index) - 0.920455*(High(index) - Low(index)))) //video 6, 0:03:58
				)
				return 0;

		if ((Low(index + 1) <= Close(index))) //por jf
			return 0;

		if (High(index) < High(index + 1))
			return 1;
		*/

	if (Open(index + 1) >= Open(index)) //por jf
		return 0;

	if ((Low(index + 1) <= Low(index)) || (High(index + 1) >= High(index))) //por jf
		return 1;

	return 2;
}

void DetectaVelaImperante(const int index)
{
	if (index == (Bars() - 1))
		velaImperante[index] = valorVelaImperante;

	int cont = index + 1;

	while (velaImperante[cont] == 0)
		cont++;

	if (High(index) > High(cont)) {
		velaImperante[index] = valorVelaImperante;
		return;
	}

	if (Low(index) < Low(cont)) {
		velaImperante[index] = valorVelaImperante;
		return;
	}

	if ((High(index) == High(cont)) && (Low(index) == Low(cont)))
	{
		velaImperante[index] = valorVelaImperante;
		return;
	}

	velaImperante[index] = 0;

	return;
}

double CalcularMA(const int index)
{
	if ((index + periodoMedia) >= Bars())
		return 0;

	SMA[index] = GetMA(index, 0, periodoMedia, (TMAType)MAtype, (TPriceType)ApplyToPrice,
		SMA[index + 1]);

	return (SMA[index] + VShift * Point());
}

EXPORT void __stdcall Calculate(int index)
{
	climaxSube[index] = 0.0;
	climaxBaja[index] = 0.0;

	internaSube[index] = 0.0;
	internaBaja[index] = 0.0;
	internaCuerpoSube[index] = 0.0;
	internaCuerpoBaja[index] = 0.0;

	externaSube[index] = 0.0;
	externaBaja[index] = 0.0;
	externaCuerpoSube[index] = 0.0;
	externaCuerpoBaja[index] = 0.0;

	MA[index] = 0.0;

	velaImperante[index] = 0.0;

	MA[index] = CalcularMA(index);

	//Dia 7, 0:08:10
	DetectaVelaImperante(index);

	if (!mostrarGatillos)
		return;

	if ((index + 1) >= Bars())
		return;

	if (MA[index + 1] == 0)
		return;

	MqlDateTime fecha;

	if (!TimeToStruct(Time(index), fecha))
		return;

	if (fecha.day_of_week == FRIDAY)
		return;

	//if (MA[index + 1] <= MA[index])
	if (MA.GetValue(index + 1) <= MA.GetValue(index))
		if (climaxArriba(index))
			climaxSube[index] = Low(index);

	//if (MA[index + 1] >= MA[index])
	if (MA.GetValue(index + 1) >= MA.GetValue(index))
		if (climaxAbajo(index))
			climaxBaja[index] = High(index);

	const double valorMedia = (MA[index] + MA[index + 1]) / 2.0;

	//if (MA[index + 1] <= MA[index])
	if (MA.GetValue(index + 1) <= MA.GetValue(index))
		switch (internaArriba(index)) {
		case 1:
			if (Close(index + 1) < Open(index)) {
				if ((Close(index + 1) + fraccionPenetrando * (Open(index + 1) - Close(index + 1))) < valorMedia)
					break;

				if (Close(index + 1) > (valorMedia + distanciaMedia1 * Point()))
					break;
			}
			else
			{
				if ((Open(index) + fraccionPenetrando * (Open(index + 1) - Open(index))) < valorMedia)
					break;

				if (Open(index) > (valorMedia + distanciaMedia1 * Point()))
					break;
			}

			internaCuerpoSube[index] = Low(index);
			break;

		case 2:
			if (Low(index + 1) < Low(index)) {
				if ((Low(index + 1) + fraccionPenetrando * (High(index + 1) - Low(index + 1))) < valorMedia)
					break;

				if (Low(index + 1) > (valorMedia + distanciaMedia1 * Point()))
					break;
			}
			else
			{
				if ((Low(index) + fraccionPenetrando * (High(index + 1) - Low(index))) < valorMedia)
					break;

				if (Low(index) > (valorMedia + distanciaMedia1 * Point()))
					break;
			}

			internaSube[index] = Low(index);
			break;
		}

	//if (MA[index + 1] >= MA[index])
	if (MA.GetValue(index + 1) >= MA.GetValue(index))
		switch (internaAbajo(index)) {
		case 1:
			if (Close(index + 1) > Open(index)) {
				if ((Close(index + 1) - fraccionPenetrando * (Open(index + 1) - Close(index + 1))) > valorMedia)
					break;

				if (Close(index + 1) < (valorMedia - distanciaMedia1 * Point()))
					break;
			}
			else
			{
				if ((Open(index) - fraccionPenetrando * (Open(index) - Open(index + 1))) > valorMedia)
					break;

				if (Open(index) < (valorMedia - distanciaMedia1 * Point()))
					break;
			}

			internaCuerpoBaja[index] = High(index);
			break;
		case 2:

			if (High(index) > High(index + 1)) {
				if ((High(index) - fraccionPenetrando * (High(index) - Low(index + 1))) > valorMedia)
					break;

				if (High(index) < (valorMedia - distanciaMedia1 * Point()))
					break;
			}
			else {
				if ((High(index + 1) - fraccionPenetrando * (High(index + 1) - Low(index + 1))) > valorMedia)
					break;

				if (High(index + 1) < (valorMedia - distanciaMedia1 * Point()))
					break;
			}

			internaBaja[index] = High(index);
			break;
		}

	//if (MA[index + 1] <= MA[index])
	if (MA.GetValue(index + 1) <= MA.GetValue(index))
		switch (externaArriba(index)) {
		case 1:
			if (Close(index + 1) < Open(index)) {
				if ((Close(index + 1) + fraccionPenetrando * (Close(index) - Close(index + 1))) < valorMedia)
					break;

				if (Close(index + 1) > (valorMedia + distanciaMedia1 * Point()))
					break;
			}
			else
			{
				if ((Open(index) + fraccionPenetrando * (Close(index) - Open(index))) < valorMedia)
					break;

				if (Open(index) > (valorMedia + distanciaMedia1 * Point()))
					break;
			}

			externaCuerpoSube[index] = Low(index);
			break;
		case 2:
			if (Low(index + 1) < Low(index)) {
				if ((Low(index + 1) + fraccionPenetrando * (High(index) - Low(index + 1))) < valorMedia)
					break;

				if (Low(index + 1) > (valorMedia + distanciaMedia1 * Point()))
					break;
			}
			else
			{
				if ((Low(index) + fraccionPenetrando * (High(index) - Low(index))) < valorMedia)
					break;

				if (Low(index) > (valorMedia + distanciaMedia1 * Point()))
					break;
			}

			externaSube[index] = Low(index);
			break;
		}

	//if (MA[index + 1] >= MA[index])
	if (MA.GetValue(index + 1) >= MA.GetValue(index))
		switch (externaAbajo(index)) {
		case 1:
			if (Close(index + 1) > Open(index)) {
				if ((Close(index + 1) - fraccionPenetrando * (Close(index + 1) - Close(index))) > valorMedia)
					break;

				if (Close(index + 1) < (valorMedia - distanciaMedia1 * Point()))
					break;
			}
			else
			{
				if ((Open(index) - fraccionPenetrando * (Open(index) - Close(index))) > valorMedia)
					break;

				if (Open(index) < (valorMedia - distanciaMedia1 * Point()))
					break;
			}

			externaCuerpoBaja[index] = High(index);
			break;
		case 2:
			if (High(index + 1) > High(index)) {

				if ((High(index + 1) - fraccionPenetrando * (High(index) - Low(index + 1))) > valorMedia)
					break;

				if (High(index + 1) < (valorMedia - distanciaMedia1 * Point()))
					break;
			}
			else
			{
				if ((High(index) - fraccionPenetrando * (High(index) - Low(index))) > valorMedia)
					break;

				if (High(index) < (valorMedia - distanciaMedia1 * Point()))
					break;
			}

			externaBaja[index] = High(index);
			break;
		}

	/*
	if (TimeToStr(Time(index)) == "2013.10.15 04:00:00")
		Print("t");
*/
}