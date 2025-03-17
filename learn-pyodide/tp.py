import pygame

pygame.init()

# Set up the display
size = (400, 400)
screen = pygame.display.set_mode(size)

# Create a player object
player = pygame.Surface((50, 50))
player.fill((255, 0, 0))

# Set the initial position of the player
player_pos = [175, 175]

screen.blit(player, player_pos)
pygame.display.update()

input("Press ENTER to end")