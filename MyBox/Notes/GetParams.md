PROCEDURE GetParams(argc: INT, argv: ARRAY OF STRING, CtD: ConstData, Alpha: DOUBLE)
    FileName: STRING
    Dimf: INT
    Mid: DOUBLE

    IF ExistArg("--help", argc, argv) THEN
        ParametersError()

    IF ExistArg("-lf", argc, argv) THEN
        ListFunctions(stderr)
        EXIT(0)

    IF NOT ExistArg("-a", argc, argv) THEN
        PrintToStderr("Parameter -a is necessary.\n")
        ParametersError()
    ELSE
        Alpha = atof(GetArg("-a", argc, argv))

    IF Alpha <= 0.0 THEN
        PrintToStderr("Alpha must be greater than 0.0.\n")
        ParametersError()

    IF ExistArg("-i", argc, argv) THEN
        CtD.IncType = atoi(GetArg("-i", argc, argv))
        IF CtD.IncType < 0 OR CtD.IncType > 2 THEN
            PrintToStderr("Inclusion type must be in [0, 2].\n")
            ParametersError()
        ENDIF
    ELSE
        CtD.IncType = 0

    IF NOT ExistArg("-f", argc, argv) THEN
        PrintToStderr("Parameter -f is necessary.\n")
        ParametersError()
    ELSE
        CtD.NFunction = atoi(GetArg("-f", argc, argv))

    IF CtD.NFunction < 0 THEN
        PrintToStderr("The number of the problem must be non-negative.\n")
        ParametersError()

    IF ExistArg("-s", argc, argv) THEN
        FileName = GetArg("-s", argc, argv)
        ReadProblem(FileName, CtD)
    ELSE
        PrintToStderr("Parameter -s is necessary.\n")
        ParametersError()

    Dimf = DimfProblem(CtD.NFunction)
    IF Dimf = -1 THEN
        PrintToStderr("Dimension of the function is variable.\n")
    ENDIF

    IF Dimf ≠ -1 AND CtD.NDim ≠ Dimf THEN
        PrintToStderr("Dimension of problem != Dimension of simplex.\n")
        EXIT(1)
    ENDIF

    IF ExistArg("-tcl", argc, argv) THEN
        IF CtD.NDim ≠ 2 THEN
            PrintToStderr("Only two-dimensional graphics are allowed. Dim = %d\n", CtD.NDim)
            EXIT(1)
        ENDIF

        IF ExistArg("-w", argc, argv) THEN
            CtD.WWidth = atoi(GetArg("-w", argc, argv))
        ELSE
            CtD.WWidth = 800
        ENDIF

        CtD.XLim.resize(2)
        CtD.XLim = CtD.InitBox

        IF width(CtD.XLim(0)) < width(CtD.XLim(1)) THEN
            Mid = mid(CtD.XLim(0))
            CtD.XLim(0).lower() = Mid - width(CtD.XLim(1))/2.0
            CtD.XLim(0).upper() = Mid + width(CtD.XLim(1))/2.0
        ELSE
            Mid = mid(CtD.XLim(1))
            CtD.XLim(1).lower() = Mid - width(CtD.XLim(0))/2.0
            CtD.XLim(1).upper() = Mid + width(CtD.XLim(0))/2.0
        ENDIF

        CtD.Draw = (UCHAR) atoi(GetArg("-tcl", argc, argv))
        PRINT(CtD.WWidth)
        PRINT(CtD.WWidth)
        PRINT("1")  // Number of Windows. Now just one.
        PRINT(argv[0])  // Window title
        PRINT(Alpha)
        PRINT(NamefProblem(CtD.NFunction))
        PRINT(basename(FileName))
    ELSE
        CtD.Draw = False

    ENDIF
END PROCEDURE
