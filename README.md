# CPSC-4310-project

## Usage

`make` - Compiles Apriori, Idea1 and GenDatabase programs

Their respective targets are:
```
make Apriori
make Idea1
make GenDatabase
```
Cleaning the executables:
```
make clean
```

---

To create database files:
```
./GenDatabase
```

**To run Apriori/Idea1 implementation:**
```
./executable <filename> <min_sup>
```

example:
```
./Apriori ./databases/D1K.txt 0.01
```

## Results

**Apriori**
```
D1K 0.15 - 2 DB Scans, 0.06s
D1K 0.10 - 3 DB Scans, 0.79s
D1K 0.08 - 3 DB Scans, 3.35s
D1K 0.05 - 3 DB Scans, 3.36s
D1K 0.01 - 4 DB Scans, 5.27s

D10K 0.15 - 2 DB Scans, 0.55s
D10K 0.10 - 3 DB Scans, 7.00s
D10K 0.08 - 3 DB Scans, 33.46s
D10K 0.05 - 3 DB Scans, 33.22s
D10K 0.01 - 4 DB Scans, 51.10s

D50K 0.15 - 2 DB Scans, 3.12s
D50K 0.10 - 3 DB Scans, 36.11s
D50K 0.08 - 3 DB Scans, 192.80s
D50K 0.05 - 3 DB Scans, 180.82s
D50K 0.01 - 4 DB Scans, 277.02s

D100K 0.15 - 2 DB Scans, 6.37s
D100K 0.10 - 3 DB Scans, 83.27s
D100K 0.08 - 3 DB Scans, 379.13s
D100K 0.05 - 3 DB Scans, 353.44s
D100K 0.01 - 4 DB Scans, 600.88s
```

**Idea 1**
```
D1K 0.15 - 1.0 DB Scans, 0.06s
D1K 0.10 - 2.0 DB Scans, 0.77s
D1K 0.08 - 2.0 DB Scans, 3.34s
D1K 0.05 - 1.7 DB Scans, 3.28s
D1K 0.01 - 1.1 DB Scans, 4.20s

D10K 0.15 - 1.0 DB Scans, 0.60s
D10K 0.10 - 2.0 DB Scans, 6.89s
D10K 0.08 - 1.9 DB Scans, 33.07s
D10K 0.05 - 1.5 DB Scans, 32.72s
D10K 0.01 - 1.1 DB Scans, 45.34s

D50K 0.15 - 1.0 DB Scans, 3.12s
D50K 0.10 - 2.0 DB Scans, 33.32s
D50K 0.08 - 1.8 DB Scans, 166.98s
D50K 0.05 - 1.5 DB Scans, 164.17s
D50K 0.01 - 1.1 DB Scans, 273.16s

D100K 0.15 - 1.0 DB Scans, 6.25s
D100K 0.10 - 2.0 DB Scans, 81.15s
D100K 0.08 - 1.8 DB Scans, 347.98s
D100K 0.05 - 1.5 DB Scans, 329.25s
D100K 0.01 - 1.1 DB Scans, 533.55s
```
