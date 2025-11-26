# 🧙‍♂️ Logic Wizard

> Um jogo educacional que une **lógica proposicional** e **diversão**, desenvolvido pelo **Los Macacos Studio**.

---

## 👥 Autores
- **Allysson Muniz**
- **Lucas Chaves**
- **Fernando Marinho**
- **Matheus Andrade**

---

## 🧠 Contexto do Jogo

Em um universo digital, dois magos poderosos mantêm o equilíbrio do sistema:
- **Diego – O Mago do Código**
- **Guilherme – O Mago da Lógica**

O caos começa quando o **Núcleo Corrompido** surge, espalhando bugs e ameaçando a estabilidade do sistema. Você é o programa escolhido para restaurar a harmonia, utilizando **Equivalências Lógicas e Tabelas Verdade** para derrotar os inimigos e reparar o universo digital.

> O destino do sistema está nas suas mãos.

---

## 🎮 Mecânicas Principais

### 📌 Movimentação – Teclas **WASD**
| Tecla | Ação |
|------|------|
| **W** | Move para cima |
| **A** | Move para a esquerda |
| **S** | Move para baixo |
| **D** | Move para a direita |

### 🔫 Ataques
| Tecla | Ação |
|------|------|
| **V** | Disparo frontal (1 de dano) |
| **F** | Disparo especial – 4 direções (4 de dano) |

### 📦 Baús de Recompensa
Ao derrotar inimigos, baús podem surgir. Para abri-los, você deve resolver uma **tabela verdade**:

- `V` → Verdadeiro  
- `F` → Falso  
- `Enter` → Enviar resposta  

Se acertar:
✔️ Ganha pontos  
✔️ Ganha vida extra

Se errar duas vezes:
❌ O baú desaparece

### 👑 Chefes
Ao alcançar certos níveis de dano, os chefes congelam e exibem **uma expressão lógica**.  
Digite a **equivalência lógica correta** para derrotá-lo!

---

## 📜 Menu do Jogo

| Opção | Descrição |
|------|-----------|
| **História** | Modo principal com narrativa e chefes |
| **Extermínio** | Modo sobrevivência – foco em pontuação |
| **Tutorial** | Aprenda os comandos com os magos |
| **Créditos** | Exibe os criadores do jogo |
| **Sair** | Fecha o jogo |

---

## 🧮 Sistema de Pontuação

A pontuação é baseada em:
- Inimigos derrotados  
- Chefes eliminados  
- Resolução de baús  

Os dados são salvos em um **arquivo `.txt`**, permitindo acompanhar e quebrar o **seu high score**, especialmente no modo *Extermínio*.

---

## 🕹️ Modos de Jogo

### 📖 **História**
Enfrente hordas progressivas até o **grande chefão na horda 10**.  
As expressões lógicas ficam cada vez mais difíceis!

### 💣 **Extermínio**
Sem bosses. Sem história. Apenas **ação e pontuação**.  
Seu objetivo é eliminar o máximo de inimigos e sobreviver.

---

## 🛠️ Como Jogar (Instalação)

⚠️ **O jogo funciona apenas em Linux e MacOS**

### 1️⃣ Instale o compilador C:
sudo apt update
sudo apt install build-essential manpages-dev

### 2️⃣ Instale bibliotecas de áudio (SDL2):
sudo apt-get install libsdl2-dev libsdl2-mixer-dev

### 3️⃣ Clone o repositório:
git clone https://github.com/MatheusAS1/Logic-Wizard-.git

### 4️⃣ Acesse o diretório:
cd nome-da-pasta

### 5️⃣ Execute o jogo:
make run

### 6️⃣ 🎉 Aproveite e divirta-se!

---

## 🌟 Implementações Futuras

- Novas tabelas lógicas  
- Sistema de mercador com itens  
- Pontuação como moeda de troca  
- Expansão de modos de jogo  

---

🧠 *“A lógica é a magia que governa o código.”*  
🛠 Feito com dedicação por **Los Macacos Studio**
