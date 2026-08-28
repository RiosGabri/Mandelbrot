# Agenda

```
27/08 -> L0ǵica inicial:
    - Declaração inicial das variáveis
    - Análise do enunciado
    - Lógica dos argumentos
    - Conversão inicial de argumento(string) para int
```

```
28/08 -> Substituição do atol pelo strtol para validação das entradas
    - Implementação do errno == ERANGE (previne estouro)
    - *endptr != '\0' (Pega caractere que parou de ler -> Se esse caractere não for o fim da string ('\0'), significa que o tem letras ou símbolos inválidos)
    - argv[1] == endptr (vazio ou começa com letra)
```