# Top Billed

**Team Divide and Conquer:** Matthew Paquette, Oscar Cao, RyLee Kriener

A menu-driven C++ console program that ranks IMDb titles by rating, votes, year, or
title, and compares **merge sort vs. quicksort** (run time and comparison count) on
real IMDb data.

---

## 1. Requirements

- A C++17 compiler (`g++` or `clang++`)
- `git`
- About 1.5 GB of free disk space for the IMDb data

## 2. Get the data

This project uses two files from the official **IMDb Non-Commercial Datasets**:

| File | What it contains |
|---|---|
| `title.basics.tsv.gz` | Title ID, type, name, year, runtime, genres |
| `title.ratings.tsv.gz` | Title ID, average rating, number of votes |

The files are too large for GitHub (the basics file is close to 1 GB unzipped),
so they are **not included in this repository**. Download them from IMDb:

- Download page: https://datasets.imdbws.com/
- Documentation: https://developer.imdb.com/non-commercial-datasets/

### macOS / Linux

From the project folder, run:

```bash
cd data
curl -O https://datasets.imdbws.com/title.basics.tsv.gz
curl -O https://datasets.imdbws.com/title.ratings.tsv.gz
gunzip title.basics.tsv.gz title.ratings.tsv.gz
cd ..
```

### Windows

1. Go to https://datasets.imdbws.com/ and download `title.basics.tsv.gz` and
   `title.ratings.tsv.gz`.
2. Unzip each file with 7-Zip (or another tool that opens `.gz` files).
3. Move both `.tsv` files into the project's `data` folder.

### Check

When you're done, the `data` folder should contain:

```
data/
├── title.basics.tsv
└── title.ratings.tsv
```

The files must be **unzipped** (`.tsv`, not `.tsv.gz`) and keep these exact names.
They are listed in `.gitignore`, so they will never be committed.

## 3. Project structure

```
Proj2_DSA/
├── data/        IMDb .tsv files go here (not in Git)
├── include/     Header files (.h)
├── src/         Source files (.cpp)
├── tests/       Tests
├── CMakeLists.txt
└── README.md
```
