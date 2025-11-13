# ======================================================
#  Logic Wizard - Makefile
#  Compatível com Linux (WSL) e estruturado por pastas
# ======================================================

# 🔧 Compilador e flags
CC = gcc
CFLAGS = -Wall -Werror -g -I$(INCLUDE_DIR)

# 🧱 Estrutura de pastas
SRC_DIR     = src
INCLUDE_DIR = include
BUILD_DIR   = build
OBJ_DIR     = $(BUILD_DIR)/obj

# 🧩 Arquivos e alvo principal
PROJ_NAME = logic_wizard
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADER_FILES = $(wildcard $(INCLUDE_DIR)/*.h)
TARGET = $(BUILD_DIR)/$(PROJ_NAME)

# ======================================================
#  Regras principais
# ======================================================

# Compilação completa
all: $(BUILD_DIR) $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJ_FILES)
	@echo "🔗 Linking $(PROJ_NAME)..."
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)
	@echo "✅ Build completo! Executável gerado em $(TARGET)"

# Compilar cada arquivo .c individualmente
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_FILES)
	@echo "🧩 Compilando $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Criar diretórios
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# ======================================================
#  Limpeza e execução
# ======================================================

# Remove arquivos compilados
clean:
	@echo "🧹 Limpando arquivos de build..."
	@rm -rf $(BUILD_DIR)
	@echo "✨ Limpeza concluída."

# Compila e executa
run: all
	@echo "🚀 Executando o jogo..."
	@./$(TARGET)

# ======================================================
#  Informações
# ======================================================
# Comandos disponíveis:
#   make        -> Compila o projeto
#   make run    -> Compila e executa
#   make clean  -> Remove arquivos de build
# ======================================================
