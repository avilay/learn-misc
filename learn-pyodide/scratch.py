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

# The game loop
# The game loop
running = True
while running:
    # Check for events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        # Check for mouse inputs
        elif event.type == pygame.MOUSEBUTTONDOWN:
            mouse_x, mouse_y = event.pos
            player_pos[0] = mouse_x
            player_pos[1] = mouse_y
        elif event.type == pygame.MOUSEBUTTONUP:
            pass
        elif event.type == pygame.FINGERDOWN:
            print("Finger touched the screen")

    screen.fill((0, 0, 0))

    # Draw the player
    screen.blit(player, player_pos)

    # Update the display
    pygame.display.update()