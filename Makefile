# Definição de variáveis para os comandos do Git
GIT = git

# Solicita ao usuário uma mensagem de commit antes de executar o commit
ask_commit_message:
	@read -p "Digite a mensagem de commit: " commitMessage; \
	$(GIT) add .; \
	$(GIT) commit -m "$$commitMessage"

# Target para fazer push das mudanças
push:
	$(GIT) push

# Target para fazer pull das mudanças
pull:
	$(GIT) pull

# Target padrão que executa add, commit, push e pull
all: pull ask_commit_message push

.PHONY: ask_commit_message push pull all


