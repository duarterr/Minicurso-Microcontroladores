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

## ⚠️ Aviso Importante: Versão do Code Composer Studio

Devido a limitações atuais (maio de 2025) da versão 20 do Code Composer Studio (CCS) – como a impossibilidade de criar projetos vazios e incompatibilidades com o TivaWare SDK – **este minicurso utiliza a versão 12 do CCS**, que é plenamente compatível com os dispositivos da família Tiva C (TM4C123G).

📎 Um tutorial completo de desinstalação da versão 20 está disponível na pasta "outros".
📎 Um tutorial para download e instalação da versão 12 está disponível nos slides do minicurso.


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

# Microcontrollers Minicourse - TM4C123G

This repository contains the material for the **Microcontrollers Minicourse** taught at the Technology Center of the Federal University of Santa Maria (UFSM), through the GEDRE – Lighting Intelligence group.

## 👨‍🏫 Instructor
Prof. Renan Duarte  
[renan.duarte@gedre.ufsm.br](mailto:renan.duarte@gedre.ufsm.br)  
GEDRE – Federal University of Santa Maria

## 🧠 Objective
The course aims to introduce the main theoretical and practical concepts related to microcontroller programming, using as a basis an ARM microcontroller from the Tiva C series (TM4C123GH6PM) and the **TM4C123G LaunchPad** development board.

## 📁 Repository Structure

- `Minicurso_uC.pdf`: Slides used during the minicourse.
- `Bibliografia/`: References and supplementary materials.
- `Labs/`: Source codes for the practical classes.

> **Note:** The Code Composer Studio (CCS) projects are not included. To run the examples, it is necessary to create projects in CCS according to the instructions in the slides.

## 📚 Course Content

1. **Basic Concepts**
2. **Software Installation**
3. **Base Project**
4. **System Clock**
5. **GPIO**
6. **Interrupts**
7. **Timer**
8. **ADC**
9. **PWM**
10. **Final Challenge** - Waveform generation via PWM controlled by analog input

## 💻 Tools Used

- [Code Composer Studio (CCS)](https://www.ti.com/tool/CCSTUDIO) – Eclipse-based IDE
- [TivaWare SDK](https://www.ti.com/tool/SW-TM4C) – Texas Instruments library
- [TM4C123G LaunchPad](https://www.ti.com/lit/pdf/spmu296) board

## ⚠️ Important Notice: Code Composer Studio Version

Due to current limitations (as of May 2025) in version 20 of Code Composer Studio (CCS) – such as the inability to create empty projects and incompatibilities with the TivaWare SDK – **this minicourse uses version 12 of CCS**, which is fully compatible with devices from the Tiva C family (TM4C123G).

📎 A complete tutorial for uninstalling version 20 is available in the "outros" folder.  
📎 A tutorial for downloading and installing version 12 is available in the minicourse slides.


## 🚀 How to Use the Codes

1. **Create a new project in CCS**:
   - Select the TM4C123GH6PM microcontroller.
   - Configure the path to the TivaWare SDK.

2. **Add the source files**:
   - Copy the `.c` file from the `Labs/` folder to the project directory.

3. **Compile and load the code onto the board**:
   - Connect the board via USB.
   - Compile the project and upload it to the board.

> **Tip:** Refer to the `Minicurso_uC.pdf` file for specific configuration and usage details of each example.

## 📖 Reading Requirements

Before starting, it is recommended to read the following documents:

- [TM4C123GH6PM Datasheet](https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf)
- [TM4C123G LaunchPad Manual](https://www.ti.com/lit/pdf/spmu296)
- [TivaWare Guide](https://www.ti.com/lit/ug/spmu298e/spmu298e.pdf)

## 📫 Contact

For questions or contributions, please contact the professor or open an issue in the repository.