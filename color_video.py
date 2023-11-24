import time
import subprocess
import board
import adafruit_tcs34725
import pygame

def init_pygame():
	pygame.init()
	size = (pygame.display.Info().current_w, pygame.display.Info().current_h)
	screen = pygame.display.set_mode(size, pygame.FULLSCREEN)
	return screen

def show_image(screen, filepath):
	img = pygame.image.load(filepath)
	img = pygame.transform.scale(img, (screen.get_width(), screen.get_height()))
	screen.blit(img, (0,0))
	pygame.display.flip()

def play_video(filepath):
	return subprocess.Popen(['cvlc', '--fullscreen', filepath])

i2c = board.I2C()
sensor = adafruit_tcs34725.TCS34725(i2c)

default_image_path = '/home/shao/Videos/image2.jpg'

screen = init_pygame()

show_image(screen, default_image_path)

video_process = None
last_play_time = 0
video_duration = 10

while True:
	r, g, b =sensor.color_rgb_bytes
	print(f'Red: {r}, Green: {g}, Blie: {b}')
	current_time = time.time()
	
	if r > 30 and g < 100 and b < 100:
		if current_time - last_play_time > video_duration:
			video_process = play_video('/home/shao/Videos/video2.mp4')
			last_play_time = current_time
			show_image(screen, default_image_path)
			
	else:
		show_image(screen, default_image_path)
		
	time.sleep(1)
