FROM alpine:3.21.3

RUN apk update && apk add --no-cache nodejs npm

COPY ./site /app/
WORKDIR /app/

RUN npm install && npm run build
