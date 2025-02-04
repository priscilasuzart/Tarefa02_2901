# Tarefa 02 - Unidade 04 - Capítulo 05 - Projeto de controle de LEDs com botão  

Este projeto demonstra como controlar três LEDs (verde, azul e vermelho) usando um botão. Quando o botão é pressionado, todos os LEDs acendem e, em seguida, desligam em sequência com intervalos de 3 segundos.  

# Componentes necessários
1) Microcontrolador Raspberry Pi Pico W.  
2) 03 LEDs (azul, vermelho e verde).  
3) 03 Resistores de 330 Ω.  
4) Botão (Pushbutton).

# Esquema de conexão
Os componentes foram conectados da seguinte forma:
1) LED verde: GPIO 11.  
2) LED azul: GPIO 12.  
3) LED vermelho: GPIO 13.  
Botão: GPIO 5 (com resistor pull-up interno).

# Funcionamento do código
Ao pressionar o botão conectado ao GPIO 5:  
1) Todos os LEDs (verde, azul e vermelho) acendem.
2) Após 3 segundos, o LED azul se apaga.  
3) Após mais 3 segundos, o LED vermelho se apaga.  
4) Após mais 3 segundos, o LED verde se apaga.  
O botão só terá efeito se todos os LEDs estiverem apagados.

# Link do vídeo
https://drive.google.com/file/d/12jMcXXX2BMsWSEH7bEaKql3uSbXmU5SE/view?usp=sharing
  
# Desenvolvido por
Priscila Pereira Suzart de Carvalho

