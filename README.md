# Algorytm-X
Program rozwiązujący problem dokładnego pokrycia.

Rozwiązaniem problemu dokładnego pokrycia, dla rodziny P podzbiorów dziedziny S, jest zbiór Q⊆P taki, że każdy element dziedziny S należy do dokładnie jednego elementu Q.

Program czytający ciąg wierszy F,W1,…Wn, w którym F to filtr a W1,…Wn jest instancją problemu dokładnego pokrycia.

Wszystkie czytane wiersze są tej samej długości d. Wiersz F składa się ze znaków minus - i plus +. W każdym wierszu W1,…Wn jest co najmniej jeden znak różny od podkreślenia _.

Wynikiem programu jest ciąg wierszy reprezentujących rozwiązania instancji W1,…Wn, przekształconych następnie za pomoca filtru F przez usunięcie znaków z pozycji, na których w filtrze jest -.

Rozwiązaniem instancji W1,…Wn jest zbiór Q⊆{1,…n}, reprezentowany przez tekst R długości d. Tekst ten nie zawiera znaku podkreślenia _ i spełnia warunek

∀1≤i≤d ∃j∈Q ((Wj)i=Ri∧∀k∈Q∖{j}(Wk)i=_)

Rozwiązania są budowane ze znaków wierszy W1,…Wn, zgodnie z ich kolejnością. W danym rozwiązaniu, w kolejności od początku, wybieramy metodą prób i błędów znaki nie kolidujące z wyborami dokonanymi wcześniej.
