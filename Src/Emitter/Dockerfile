FROM builder-2024-05:ver_1 AS built

FROM ubuntu:latest
COPY --from=built /app/Emitter/Bin/emitter /app/emitter

EXPOSE 8080

CMD ["/app/emitter"]

