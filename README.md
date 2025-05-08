# Minicurso de Microcontroladores - TM4C123G

Este repositório contém o material do **Minicurso de Microcontroladores** ministrado no Centro de Tecnologia da Universidade Federal de Santa Maria (UFSM), através do grupo GEDRE – Inteligência em Iluminação.

## 👨‍🏫 Instrutor
Prof. Renan Duarte  
[renan.duarte@gedre.ufsm.br](mailto:renan.duarte@gedre.ufsm.br)  
GEDRE – Universidade Federal de Santa Maria

## 🧠 Objetivo
O curso visa introduzir os principais conceitos teóricos e práticos relacionados à programação de microcontroladores, utilizando como base um microcontrolador ARM da série Tiva C (TM4C123GH6PM) e a placa de desenvolvimento **TM4C123G LaunchPad**.

## 📁 Estrutura do Repositório

- `Minicurso_uC.pdf`: Slides utilizados durante o minicurso.
- `Bibliografia/`: Referências e materiais complementares.
- `Labs/`: Códigos-fonte das aulas práticas.

> **Nota:** Os projetos do Code Composer Studio (CCS) não estão incluídos. Para executar os exemplos, é necessário criar projetos no CCS conforme as instruções nos slides.

## 📚 Conteúdo Programático

1. **Conceitos básicos**
2. **Instalação dos softwares**
3. **Projeto base**
4. **System Clock**
5. **GPIO**
6. **Interrupções**
7. **Timer**
8. **ADC**
9. **PWM**
10. **Desafio Final** - Geração de formas de onda via PWM controladas por entrada analógica

## 💻 Ferramentas Utilizadas

- [Code Composer Studio (CCS)](https://www.ti.com/tool/CCSTUDIO) – IDE baseada em Eclipse
- [TivaWare SDK](https://www.ti.com/tool/SW-TM4C) – Biblioteca da Texas Instruments
- Placa [TM4C123G LaunchPad](https://www.ti.com/lit/pdf/spmu296)

## 🚀 Como Utilizar os Códigos

1. **Crie um novo projeto no CCS**:
   - Selecione o microcontrolador TM4C123GH6PM.
   - Configure o caminho para o TivaWare SDK.

2. **Adicione os arquivos-fonte**:
   - Copie o arquivo `.c` da pasta `Labs/` para o diretório do projeto.

3. **Compile e carregue o código na placa**:
   - Conecte a placa via USB.
   - Compile o projeto e faça o upload para a placa.

> **Dica:** Consulte o arquivo `Minicurso_uC.pdf` para detalhes específicos de configuração e uso de cada exemplo.

## 📖 Requisitos de Leitura

Antes de começar, recomenda-se a leitura dos seguintes documentos:

- [Datasheet do TM4C123GH6PM](https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf)
- [Manual do LaunchPad TM4C123G](https://www.ti.com/lit/pdf/spmu296)
- [Guia do TivaWare](https://www.ti.com/lit/ug/spmu298e/spmu298e.pdf)

## 📫 Contato

Para dúvidas ou contribuições, entre em contato com o professor ou abra uma issue no repositório.

---
