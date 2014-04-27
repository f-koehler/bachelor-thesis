ISING=../../code/ising1d/ising1d
PY=python

SMALL_N=128
BIG_N=8192
BAL_MANY=512
BAL_FEW=8192
STEP=0.01
T_1 = 0.0000001
T_2 = 5.0
h_1 = -5.0
h_2 = 5.0

all: results.pdf
results.pdf: ../header.tex ising1d.tex plot_many plot_few
	../buildtex.sh ising1d.tex
	../buildtex.sh ising1d.tex
many/heating_J1.txt:
	$(ISING) temperature --cold -N $(BIG_N) --start $(T_1) --stop $(T_2) --step $(STEP) --balance $(BAL_MANY) -J 1.0 -l $@
many/heating_J2.txt:
	$(ISING) temperature --cold -N $(BIG_N) --start $(T_1) --stop $(T_2) --step $(STEP) --balance $(BAL_MANY) -J 2.0 -l $@
many/heating_h1.txt:
	$(ISING) temperature --cold -N $(BIG_N) --start $(T_1) --stop $(T_2) --step $(STEP) --balance $(BAL_MANY) -h 1.0 -l $@
many/heating_h2.txt:
	$(ISING) temperature --cold -N $(BIG_N) --start $(T_1) --stop $(T_2) --step $(STEP) --balance $(BAL_MANY) -h 2.0 -l $@
many/cooling_J1.txt:
	$(ISING) temperature -N $(BIG_N) --start $(T_2) --stop $(T_1) --step $(STEP) --balance $(BAL_MANY) -J 1.0 -l $@
many/cooling_J2.txt: 
	$(ISING) temperature -N $(BIG_N) --start $(T_2) --stop $(T_1) --step $(STEP) --balance $(BAL_MANY) -J 2.0 -l $@
many/cooling_h1.txt: 
	$(ISING) temperature -N $(BIG_N) --start $(T_2) --stop $(T_1) --step $(STEP) --balance $(BAL_MANY) -h 1.0 -l $@
many/cooling_h2.txt: 
	$(ISING) temperature -N $(BIG_N) --start $(T_2) --stop $(T_1) --step $(STEP) --balance $(BAL_MANY) -h 2.0 -l $@
many/cooling.txt: 
	$(ISING) temperature  -N $(BIG_N) --start $(T_2) --stop $(T_1) --step $(STEP) --balance $(BAL_MANY) -h 1.0 -J 1.0 -l $@
many/mag_T0.txt: 
	$(ISING) magnetization -N $(BIG_N) --start $(h_1) --stop $(h_2) --step $(STEP) --balance $(BAL_MANY) -T 0.0 -l $@
many/mag_T1.txt: 
	$(ISING) magnetization -N $(BIG_N) --start $(h_1) --stop $(h_2) --step $(STEP) --balance $(BAL_MANY) -T 1.0 -l $@
many/mag_T2.txt: 
	$(ISING) magnetization -N $(BIG_N) --start $(h_1) --stop $(h_2) --step $(STEP) --balance $(BAL_MANY) -T 2.0 -l $@
many/mag_J0.txt: 
	$(ISING) magnetization -N $(BIG_N) --start $(h_1) --stop $(h_2) --step $(STEP) --balance $(BAL_MANY) -T 1.0 -l $@
many/mag_J1.txt: 
	$(ISING) magnetization -N $(BIG_N) --start $(h_1) --stop $(h_2) --step $(STEP) --balance $(BAL_MANY) -T 1.0 -J 1.0 -l $@
many/mag_J2.txt: 
	$(ISING) magnetization -N $(BIG_N) --start $(h_1) --stop $(h_2) --step $(STEP) --balance $(BAL_MANY) -T 1.0 -J 2.0 -l $@
few/heating_J1.txt: 
	$(ISING) temperature --cold -N $(SMALL_N) --start $(T_1) --stop $(T_2) --step $(STEP) --balance $(BAL_FEW) -J 1.0 -l $@
few/heating_J2.txt: 
	$(ISING) temperature --cold -N $(SMALL_N) --start $(T_1) --stop $(T_2) --step $(STEP) --balance $(BAL_FEW) -J 2.0 -l $@
few/heating_h1.txt: 
	$(ISING) temperature --cold -N $(SMALL_N) --start $(T_1) --stop $(T_2) --step $(STEP) --balance $(BAL_FEW) -h 1.0 -l $@
few/heating_h2.txt: 
	$(ISING) temperature --cold -N $(SMALL_N) --start $(T_1) --stop $(T_2) --step $(STEP) --balance $(BAL_FEW) -h 2.0 -l $@
few/cooling_J1.txt: 
	$(ISING) temperature -N $(SMALL_N) --start $(T_2) --stop $(T_1) --step $(STEP) --balance $(BAL_FEW) -J 1.0 -l $@
few/cooling_J2.txt: 
	$(ISING) temperature -N $(SMALL_N) --start $(T_2) --stop $(T_1) --step $(STEP) --balance $(BAL_FEW) -J 2.0 -l $@
few/cooling_h1.txt: 
	$(ISING) temperature -N $(SMALL_N) --start $(T_2) --stop $(T_1) --step $(STEP) --balance $(BAL_FEW) -h 1.0 -l $@
few/cooling_h2.txt: 
	$(ISING) temperature -N $(SMALL_N) --start $(T_2) --stop $(T_1) --step $(STEP) --balance $(BAL_FEW) -h 2.0 -l $@
few/cooling.txt: 
	$(ISING) temperature  -N $(SMALL_N) --start $(T_2) --stop $(T_1) --step $(STEP) --balance $(BAL_FEW) -h 1.0 -J 1.0 -l $@
few/mag_T0.txt: 
	$(ISING) magnetization -N $(SMALL_N) --start $(h_1) --stop $(h_2) --step $(STEP) --balance $(BAL_FEW) -T 0.0 -l $@
few/mag_T1.txt: 
	$(ISING) magnetization -N $(SMALL_N) --start $(h_1) --stop $(h_2) --step $(STEP) --balance $(BAL_FEW) -T 1.0 -l $@
few/mag_T2.txt: 
	$(ISING) magnetization -N $(SMALL_N) --start $(h_1) --stop $(h_2) --step $(STEP) --balance $(BAL_FEW) -T 2.0 -l $@
few/mag_J0.txt: 
	$(ISING) magnetization -N $(SMALL_N) --start $(h_1) --stop $(h_2) --step $(STEP) --balance $(BAL_FEW) -T 1.0 -l $@
few/mag_J1.txt: 
	$(ISING) magnetization -N $(SMALL_N) --start $(h_1) --stop $(h_2) --step $(STEP) --balance $(BAL_FEW) -T 1.0 -J 1.0 -l $@
few/mag_J2.txt: 
	$(ISING) magnetization -N $(SMALL_N) --start $(h_1) --stop $(h_2) --step $(STEP) --balance $(BAL_FEW) -T 1.0 -J 2.0 -l $@

.PHONY: clean plot_many plot_few
clean:
	rm -rf many/* few/* *.pdf __pycache__
	../cleantex.sh
plot_many: many/heating_J1.txt many/heating_J2.txt many/heating_h1.txt many/heating_h2.txt many/cooling_J1.txt many/cooling_J2.txt many/cooling_h1.txt many/cooling_h2.txt many/cooling.txt many/mag_T0.txt many/mag_T1.txt many/mag_T2.txt many/mag_J0.txt many/mag_J1.txt many/mag_J2.txt
	$(PY) plot_many.py
plot_few: few/heating_J1.txt few/heating_J2.txt few/heating_h1.txt few/heating_h2.txt few/cooling_J1.txt few/cooling_J2.txt few/cooling_h1.txt few/cooling_h2.txt few/cooling.txt few/mag_T0.txt few/mag_T1.txt few/mag_T2.txt few/mag_J0.txt few/mag_J1.txt few/mag_J2.txt
	$(PY) plot_few.py
