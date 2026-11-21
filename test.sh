#!/bin/bash

# Compilación con sanitizadores para detectar fallos de memoria al vuelo
# (si quieres compilar sin sanitizadores, quita -fsanitize=address,undefined)
gcc -Wall -Wextra -fsanitize=address,undefined v2_shunting_yard.c -lm -o calc || exit 1

errors=""
test_num=0
passed=0

# Prueba expresiones VÁLIDAS (deben salir con código 0 y resultado dentro de tolerancia)
run_test() {
    local expr="$1"
    local expected="$2"
    ((test_num++))

    local output exit_code
    output=$(printf "%s" "$expr" | ./calc 2>/dev/null)
    exit_code=$?

    if [ "$exit_code" -ge 128 ]; then
        errors+="Test $test_num ($expr) CRASHED (signal $((exit_code - 128))).\n"
        return
    fi

    if [ "$exit_code" -ne 0 ] || [[ ! "$output" =~ ^-?[0-9]+(\.[0-9]+)?$ ]]; then
        errors+="Test $test_num ($expr) FAILED.\n\tExpected: $expected (exit 0)\n\tObtained: '$output' (exit $exit_code)\n"
        return
    fi

    local ok
    ok=$(echo "scale=10; d = ($output) - ($expected); if (d < 0) d = -d; d <= 0.00001" | bc -l)
    if [ "$ok" -eq 1 ]; then
        ((passed++))
    else
        errors+="Test $test_num ($expr) FAILED.\n\tExpected: $expected\n\tObtained: $output\n"
    fi
}

# Prueba expresiones INVÁLIDAS (deben fallar limpiamente: exit != 0 y sin crash)
run_error_test() {
    local expr="$1"
    local reason="$2"
    ((test_num++))

    local output exit_code
    output=$(printf "%s" "$expr" | ./calc 2>/dev/null)
    exit_code=$?

    if [ "$exit_code" -ge 128 ]; then
        errors+="Error-Test $test_num ($expr) [$reason] CRASHED (signal $((exit_code - 128))).\n"
    elif [ "$exit_code" -eq 0 ]; then
        errors+="Error-Test $test_num ($expr) [$reason] FAILED.\n\tExpected: non-zero exit code (error)\n\tObtained: '$output' (exit 0)\n"
    else
        ((passed++))
    fi
}

# ==============================================================================
# 1. LITERALES, CERO Y DECIMALES
# ==============================================================================
run_test "0"                        0
run_test "42"                       42
run_test "-0"                       0
run_test "+0"                       0
run_test "007+003"                  10
run_test "0.000+0.000"              0
run_test ".5"                       0.5
run_test "5."                       5
run_test ".5+.25"                   0.75
run_test "-.5*-.5"                  0.25
run_test "5.+2."                    7
run_test "0.01*0.01"                0.0001

# ==============================================================================
# 2. OPERACIONES BÁSICAS Y PUNTO FLOTANTE
# ==============================================================================
run_test "2+3"                      5
run_test "10-4"                     6
run_test "4-10"                     -6
run_test "6*7"                      42
run_test "15/4"                     3.75
run_test "1/3"                      0.333333
run_test "0.1+0.2"                  0.3
run_test "0*999999"                 0
run_test "0/5"                      0
run_test "0/-5"                     0
run_test "123456.789-123456.789"    0
run_test "10000000000+1"            10000000001
run_test "99999999999999+1"         100000000000000

# ==============================================================================
# 3. PRECEDENCIA Y ASOCIATIVIDAD
# ==============================================================================
run_test "2+3*4"                    14
run_test "2*3+4"                    10
run_test "10-3-2-1"                 4
run_test "100/10/2/5"               1
run_test "20/2*5"                   50
run_test "20*2/5"                   8
run_test "1-2+3-4+5-6"              -3
run_test "100-20*3+40/2-5"          55
run_test "1+2*3-4/2+5*6/3"          15
run_test "3+4*2/(1-5)"              1  #no chambea

# ==============================================================================
# 4. OPERADORES UNARIOS (+ y -)
# ==============================================================================
run_test "-5"                       -5
run_test "+5"                       5
run_test "---5"                     -5
run_test "----5"                    5
run_test "+-+5"                     -5
run_test "5--2"                     7
run_test "5+-2"                     3
run_test "5-+2"                     3
run_test "5---2"                    3
run_test "5*-2"                     -10
run_test "5*+2"                     10
run_test "-10/-2"                   5
run_test "-2*-3+-4/-2"              8
run_test "5+-2*3"                   -1
run_test "(-5)"                     -5
run_test "-(5)"                     -5 #no chambea
run_test "-(-5)"                    5 #no chambea
run_test "-(-(-5))"                 -5 #no chambea
run_test "+(-(+(-5)))"              5 #no chambea
run_test "-(3+2)"                   -5 #no chambea
run_test "-(3+2)-1"                 -6 #no chambea
run_test "-(2+3)*-(4-1)"            15 #no chambea
run_test "10/-(2+3)"                -2 #no chambea
run_test "-(1-2-3)"                 4 #no chambea
run_test "5/+2"                     2.5

# ==============================================================================
# 5. PARÉNTESIS Y ANIDAMIENTO
# ==============================================================================
run_test "((42))"                           42
run_test "(((1+2)))"                        3
run_test "(2+3)-1"                          4
run_test "(10+5)+2"                         17
run_test "(6-2)-(3-1)"                      2 #no chambea
run_test "((4+1)*2)-5"                      5
run_test "2*(3+4)"                          14 #no chambea
run_test "(2+3)*(4+5)"                      45 #no chambea
run_test "((1.5+2.5)*(3.2-1.2))/(0.5*4)"    4 #no chambea
run_test "((2+3)*(4+5))/((6-1)*(7-4))"      3 #no chambea
run_test "1-(2-(3-(4-5)))"                  3 #no chambea
run_test "((1+2)*(3+(4*(5-2))))"            45 #no chambea

# ==============================================================================
# 6. MULTIPLICACIÓN IMPLÍCITA (opcional según especificación)
# ==============================================================================
run_test "2(3+4)"                   14 #no chambea
run_test "(2+3)(4+5)"               45 #no chambea
run_test "(2+3)4"                   20 #no chambea
run_test "2(-3)"                    -6 #no chambea
run_test "-(2)(3)"                  -6 #no chambea
run_test "2(3)(4)"                  24 #no chambea
run_test "2(3+1(4+1))"              16 #no chambea

# ==============================================================================
# 7. POTENCIACIÓN (asociatividad derecha y prioridad frente a unarios)
# ==============================================================================
run_test "2^3"                      8 #no chambea
run_test "2^0"                      1 #no chambea
run_test "5^1"                      5 #no chambea
run_test "2^3^2"                    512 #no chambea
run_test "2^3*4"                    32 #no chambea
run_test "4*2^3"                    32 #no chambea
run_test "2^-3"                     0.125 #no chambea
run_test "(-2)^2"                   4 #no chambea
run_test "(-2)^3"                   -8 #no chambea
run_test "-2^2"                     -4 #no chambea
run_test "9^0.5"                    3 #no chambea
run_test "3+4*2/(1-5)^2^3"          3.000122 #no chambea

# ==============================================================================
# 8. ESPACIOS, TABULADORES Y SALTOS DE LÍNEA
# ==============================================================================
run_test "   42   "                 42
run_test "10 + 20 * 3"              70
run_test " ( 2 + 3 ) * ( 4 - 1 ) "  15  #no chambea
run_test "- 5 + 3"                  -2
run_test "5 - - 2"                  7
run_test $'\t10\t+\t5\t'            15
run_test $'2+3*4\n'                 14

# ==============================================================================
# 9. ESTRÉS DE LONGITUD, PROFUNDIDAD Y BUFFERS
# ==============================================================================
run_test "0000000000000000000000005+1"  6  #no chambea
run_test "0.000000000000000000001+1"    1  #no chambea

# 35 signos unarios seguidos
many_unary="5"
for ((i=0; i<35; i++)); do many_unary="-$many_unary"; done
run_test "$many_unary" -5

# 50 paréntesis anidados con operaciones pendientes (estresa ambas pilas)
deep_expr="1"
for ((i=0; i<50; i++)); do deep_expr="1+($deep_expr)"; done
run_test "$deep_expr" 51  #no chambea

# 50 paréntesis vacíos de operaciones alrededor de un número
deep_parens="42"
for ((i=0; i<50; i++)); do deep_parens="($deep_parens)"; done
run_test "$deep_parens" 42 #no chambea

# 100 sumas encadenadas
long_sum="1"
for ((i=1; i<100; i++)); do long_sum+="+1"; done
run_test "$long_sum" 100

# ==============================================================================
# 10. ERRORES QUE UNA CALCULADORA COMPLETA DEBE RECHAZAR LIMPIAMENTE
# ==============================================================================
# Entrada vacía o solo espacios
run_error_test ""                   "empty input"
run_error_test "     "              "whitespace only"
run_error_test $'\n'                "only newline"

# División por cero (literal y evaluada)
run_error_test "10/0"               "division by zero"
run_error_test "0/0"                "0/0 indeterminate"
run_error_test "5/(3-3)"            "computed division by zero"
run_error_test "10/0+5"             "must abort after div by zero"
run_error_test "1/(2-4/2)"          "nested division by zero"

# Paréntesis desbalanceados o vacíos
run_error_test "()"                 "empty parentheses"
run_error_test "2+()"               "empty parentheses in expr"
run_error_test "(2+3"               "unclosed parenthesis"
run_error_test "((2+3)"             "unclosed nested parenthesis"
run_error_test "2+3)"               "unexpected closing parenthesis"
run_error_test ")"                  "lone closing parenthesis"
run_error_test "("                  "lone opening parenthesis"
run_error_test ")("                 "reversed parentheses"

# Operandos faltantes y operadores binarios consecutivos
run_error_test "+"                  "lone unary +"
run_error_test "-"                  "lone unary -"
run_error_test "*"                  "lone binary *"
run_error_test "/"                  "lone binary /"
run_error_test "5+"                 "trailing +"
run_error_test "5-"                 "trailing -"
run_error_test "5*"                 "trailing *"
run_error_test "5/"                 "trailing /"
run_error_test "*5"                 "leading *"
run_error_test "/5"                 "leading /"
run_error_test "5+*2"               "consecutive binary +*"
run_error_test "5*/2"               "consecutive binary */"
#run_error_test "5/+2"               "binary / followed by +?" # Quita esta si permites 5/(+2) = 2.5
run_error_test "5**2"               "consecutive **"
run_error_test "5//2"               "consecutive //"
run_error_test "(*5)"               "leading binary inside parens"
run_error_test "(5+)"               "trailing binary inside parens"
run_error_test "(-)"                "unary without operand inside parens"
run_error_test "(+)"                "unary + without operand inside parens"

# Números mal formados y espacios entre operandos
run_error_test "."                  "lone period"
run_error_test ".+."                "periods without digits"
run_error_test "..5"                "double leading period"
run_error_test "1.2.3"              "multiple decimal points"
run_error_test "1.2.3+4"            "multiple decimal points in expr"
run_error_test "12 34"              "two numbers separated by space"
run_error_test "12 34 + 5"          "missing operator between numbers"

# Caracteres no válidos
run_error_test "abc"                "letters only"
run_error_test "2+a"                "unknown variable"
run_error_test "12abc34+1"          "letters inside number"
run_error_test "2,5+1"              "comma instead of dot"
run_error_test "2+3=5"              "equals sign"

# Errores de dominio en potenciación (si implementas ^)
run_error_test "(-4)^0.5"           "even root of negative number"
run_error_test "0^-1"               "zero to negative power"

# ==============================================================================
# RESUMEN
# ==============================================================================
echo "Passed: $passed / $test_num"
if [ -z "$errors" ]; then
    echo "All $test_num tests passed!"
else
    echo -e "\n$errors"
    exit 1
fi
