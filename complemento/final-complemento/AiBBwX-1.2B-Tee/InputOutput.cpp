/***************************************************************************
                          InputOutput.cpp  -  description
                             -------------------
    begin                : Jan 2020
    copyright            : (C) 2020 by L.G. Casado
    email                : leo@ual.es
 ***************************************************************************/
#include "InputOutput.hpp"

/*----------------------------------------------------------------------------*/
void ParametersError()
{
   fputs("Options are:\n", stderr);
   fputs("\t[ --help To show this help ],\n", stderr);
   fputs("\t[ -lf to list functions    ],\n", stderr);
   fputs("\t -f              <int>: fucntion number (see -lf),\n", stderr);
   fputs("\t -s     <box file>:\n", stderr);
   fputs("\t -e             <real>: acurracy for w(X),\n", stderr);
   fputs("\t -nmt                 : No monotonicity test,\n", stderr);
   fputs("\t -cavl           <int>: check avl tree after int iter,\n", stderr);
   fputs("\t[ -i                  : Inclusion type:\n", stderr);
   fputs("\t\t\t\t 0:IA,\n", stderr);
   fputs("\t\t\t\t 1:CFcBox, 2:CFbBox, 3:AA (Not jet) \n", stderr);
   fputs("\t[ -w             <int>: Graphic window width (800)],\n", stderr);
   fputs("\t[ -tcl           <int>: Graph output with\"| WinZoom.tcl\"].\n", stderr);
   fprintf(stderr, "\t                       1: normal draw, 2:steps,");

   exit(0);
}

/*---------------------------------------------------------------------------*/
void CheckMagicNumber(FILE *FIn)
{
   // File is aready open.
   INT MagicNumber; /*End of input Archive, to know if all was readed*/
   char cadena[256], cadena1[256];

   fscanf(FIn, "%s %s", cadena, cadena1);
   MagicNumber = atoi(cadena1);
   if (MagicNumber != 123456)
   {
      fprintf(stderr, "Error reading input file, MagicNumber=%d.\n",
              MagicNumber);
      exit(1);
   }
}

/*---------------------------------------------------------------------------*/
/*Read the vertices of the problem.                                          */
/*---------------------------------------------------------------------------*/
VOID ReadProblem(PCHAR FileName, ConstData &CtD)
{
   FILE *FIn;

   char cadena[256], cadena1[256];

   FIn = OpenFile(FileName, "r");

   // Check if the searxh region is simplex or a Box
   fscanf(FIn, "%s", cadena);

   if (!strcmp(cadena, "Box") == 0)
   {
      fprintf(stderr, "ReadProblem: It is not a Box.\n");
      exit(1);
   }

   /*Number of Dimensions*/
   fscanf(FIn, "%s %s ", cadena, cadena1);
   CtD.NDim = atoi(cadena1);

   if (CtD.NDim <= 0 || CtD.NDim > 32)
   {
      fprintf(stderr, "Dimension d have to be 0<d<32.\n");
      exit(1);
   }

   // We had a return. The search region is a Box.
   CtD.InititvV.resize(CtD.NDim);

   // Get Box data
   for (int i = 0; i < CtD.NDim; i++) // c-xsc starts in 1
   {
      fscanf(FIn, "%s", cadena);
      CtD.InititvV(i).lower() = atof(cadena);
      fscanf(FIn, "%s", cadena);
      CtD.InititvV(i).upper() = atof(cadena);
   }

   CheckMagicNumber(FIn);
   // Minimum
   fscanf(FIn, "%s	%s", cadena, cadena1);
   CtD.Min = atof(cadena1);
   fprintf(stderr, "Min=%g.\n", CtD.Min);
   CloseFile(FIn);
}

/*---------------------------------------------------------------------------*/
void SetXLim(PPREAL &ppR, itvV &iV, const int NDim)
{
   int i, j;

   for (j = 0; j < NDim; j++)
   {
      iV(j).lower() = ppR[0][j];
      iV(j).upper() = ppR[0][j];
   }

   for (i = 1; i < NDim + 1; i++)
      for (j = 0; j < NDim; j++)
      {
         if (ppR[i][j] < iV(j).lower())
            iV(j).lower() = ppR[i][j];
         if (ppR[i][j] > iV(j).upper())
            iV(j).upper() = ppR[i][j];
      }
}

/*---------------------------------------------------------------------------*/
// ppR initial points in input file
void GetParams(int argc, PPCHAR argv, ConstData &CtD, double &Epsilon)
{
   PCHAR FileName = NULL;
   int Dimf;
   double Mid;

   /* Check the input parameters.-- -----------------------------------------*/
   if (ExistArg("--help", argc, argv))
      ParametersError();

   if (ExistArg("-lf", argc, argv))
   {
      ListFunctions(stderr);
      exit(0);
   }

   /*-------------------------------*/
   if (!ExistArg("-e", argc, argv))
   {
      fputs("Parameter -e is neccesary.\n", stderr);
      ParametersError();
   }
   else
      Epsilon = atof(GetArg("-e", argc, argv));

   if (Epsilon <= 0.0)
   {
      fputs("Epsilon have to be >0.0.\n", stderr);
      ParametersError();
   }

   /*-------------------------------*/
   if (!ExistArg("-nmt", argc, argv))
      CtD.MonTest = true;
   else
      CtD.MonTest = false;

   /*-------------------------------*/
   if (!ExistArg("-cavl", argc, argv))
      CtD.NCheckAVL = 0;
   else
      CtD.NCheckAVL = atoi(GetArg("-cavl", argc, argv));

   if (CtD.NCheckAVL < 0)
   {
      fputs("NCeckAVL is negative.\n", stderr);
      ParametersError();
   }

   /*-------------------------------*/
   if (ExistArg("-i", argc, argv))
   {
      CtD.IncType = atoi(GetArg("-i", argc, argv));
      if (CtD.IncType < 0 || CtD.IncType > 2)
      {
         fputs("Inclusion type have to be in [0,2].\n", stderr);
         ParametersError();
      }
   }
   else
      CtD.IncType = 0;

   /*-------------------------------*/
   if (!ExistArg("-f", argc, argv))
   {
      fputs("Parameter -f is neccesary.\n", stderr);
      ParametersError();
   }
   else
      CtD.NFunction = atoi(GetArg("-f", argc, argv));

   if (CtD.NFunction < 0)
   {
      fputs("The number of the problem must be non negative.\n", stderr);
      ParametersError();
   }

   // ReadProblem. Some imput parameters has default values as NDim.
   // They have to be checek after reading the file.
   if (ExistArg("-s", argc, argv))
   {
      FileName = GetArg("-s", argc, argv);
      ReadProblem(FileName, CtD);
   }
   else
   {
      fputs("Parameter -s is neccesary.\n", stderr);
      ParametersError();
   }

   /*-------------------------------*/
   Dimf = DimfProblem(CtD.NFunction);
   if (Dimf == -1)
      fprintf(stderr, "Dimension of the %s function is variable,\n",
              NamefProblem(CtD.NFunction));

   if (Dimf != -1 && CtD.NDim != Dimf)
   {
      fprintf(stderr, "Dim of problem=%d != Dim of simplex =%d.\n",
              Dimf, CtD.NDim);
      exit(1);
   }

   /*-------------------------------*/
   if (ExistArg("-tcl", argc, argv))
   {
      if (CtD.NDim != 2)
      {
         fprintf(stderr, "Only two dimensinal graphics are allowed. Dim=%d\n",
                 CtD.NDim);
         exit(1);
      }

      /*-------------------------------*/
      if (ExistArg("-w", argc, argv))
         CtD.WWidth = atoi(GetArg("-w", argc, argv));
      else
         CtD.WWidth = 800;

      CtD.XLim.resize(2);
      CtD.XLim = CtD.InititvV; // TODO: two things for the same.

      if (width(CtD.XLim(0)) < width(CtD.XLim(1)))
      {
         Mid = mid(CtD.XLim(0));
         CtD.XLim(0).lower() = Mid - width(CtD.XLim(1)) / 2.0;
         CtD.XLim(0).upper() = Mid + width(CtD.XLim(1)) / 2.0;
      }
      else
      {
         Mid = mid(CtD.XLim(1));
         CtD.XLim(1).lower() = Mid - width(CtD.XLim(0)) / 2.0;
         CtD.XLim(1).upper() = Mid + width(CtD.XLim(0)) / 2.0;
      }

      CtD.Draw = (UCHAR)atoi(GetArg("-tcl", argc, argv));
      printf("%d\n", CtD.WWidth);
      printf("%d\n", CtD.WWidth);
      printf("1\n");           // Number of Windows. Now just one.
      printf("%s\n", argv[0]); // window title
      printf("%g\n", Epsilon);
      // printf("%d\n",CtD.NFunction);
      printf("%s\n", NamefProblem(CtD.NFunction));
      printf("%s\n", basename(FileName));
   }
   else
      CtD.Draw = False;
}

/*---------------------------------------------------------------------------*/
void PrintParams(FILE *FOut, ConstData &CtD, double Epsilon)
{

   fprintf(FOut, "NDim=        %d.\n", CtD.NDim);
   fprintf(FOut, "NFunction   =%d.\n", CtD.NFunction);
   fprintf(FOut, "Function    =%s.\n", NamefProblem(CtD.NFunction));
   fprintf(FOut, "Epsilon       =%f.\n", Epsilon);
   fprintf(FOut, "IncType     =%d.\n", (int)CtD.IncType);
   fprintf(FOut, "Draw        =%d.\n", (int)CtD.Draw);
   fprintf(FOut, "NWin        =%d.\n", CtD.NWin);
   fprintf(FOut, "WWidth      =%d.\n", CtD.WWidth);
   cerr << "XLim        =" << endl
        << CtD.XLim << endl;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
