from decimal import Decimal, getcontext
getcontext().prec = 1000000000
getcontext().Emax = 9999999999
a = pow(Decimal(2), 82589933) - 1