FROM golang:1.18.5

RUN mkdir /app
ADD . /app/

WORKDIR /app

RUN go build -o main .

CMD ["./main"]