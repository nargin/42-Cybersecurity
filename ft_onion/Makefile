DOCKER_IMAGE = ft_onion
DOCKER_CONTAINER = ft_onion-container

include .env
export $(shell sed 's/=.*//' .env)

all: docker-build

docker-build: stop docker-clean
	@docker build --build-arg SSH_USER=$(SSH_USER) --build-arg SSH_PASSWORD=$(SSH_PASSWORD) -t $(DOCKER_IMAGE) -f dockerfile .

docker-run:
	@docker run -d -p 80:80 -p 4242:4242 --name $(DOCKER_CONTAINER) $(DOCKER_IMAGE)

clean:
	@docker rmi -f $(DOCKER_IMAGE) || true

stop:
	@docker stop $(DOCKER_CONTAINER) || true
	@docker rm $(DOCKER_CONTAINER) || true

docker-prune: clean
	@docker system prune -f

run: docker-build docker-run

hostname:
	@docker exec -it $(DOCKER_CONTAINER) cat /var/lib/tor/hidden_service/hostname

test: run
	sleep 5
	@docker exec -it $(DOCKER_CONTAINER) /app/test_onion.sh

.PHONY: all build docker-build docker-run docker-clean stop docker-prune run hostname test
